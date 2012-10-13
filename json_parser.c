#include "json_parser.h"
#include "jsmn.h"
#include "config.h"
#include "logger.h"
#include "alarm.h"
#include "valf.h"
#include "Irrigation.h"
#include <stdio.h>
#include <string.h>

#define SENSORS_TAG             "sensors"
#define ID_TAG                  "id"
#define ALARM_TAG               "alarms"
#define PORT_INDEX_TAG          "port_index"
#define ALARM_VALUE_TAG         "alarm_value"
#define CONDITION_TYPE_TAG      "condition_type"
#define MAX_NUMBER_OF_TOKENS    100
#define REFRESH_RATE_TAG        "refresh_rate_seconds"
#define MAIN_VALF_DELAY_TAG     "main_valve_delay"
#define MAIN_VALF_TAG           "main_valf"

#define START_TIME_TAG          "start_time"
#define VALF_ID_TAG             "valf_id"
#define IRRIGATION_MODE_TAG     "irrigation_mode"
#define AMOUNT_TAG              "amount"

#define IRRIGATION_MODE_VOLUME  "volume"
#define IRRIGATION_MODE_TIME    "time"

// Useful macro to compare between the string of the tag (t) and a string (s).
#define TOKEN_STRING(js, t, s) \
	(strncmp(js+(t).start, s, (t).end - (t).start) == 0 \
	 && strlen(s) == (t).end - (t).start)

static bool json_parse(const char *json_buffer, TokenVector *tokens);
static int find_json_array_token(TokenVector *tokens, const char* json_buffer, const char* token_key);
static bool token_to_int(const char* json_buffer, jsmntok_t *token, int *value);
static bool token_to_uint(const char* json_buffer, jsmntok_t *token, size_t *value);
static bool token_to_double(const char* json_buffer, jsmntok_t *token, double *value);
static bool json_parse_sensors_internal(TokenVector* tokens, const char* json_buffer, ListElement* sensors);
static bool json_parse_alarms_internal(TokenVector* tokens, const char* json_buffer, ListElement* sensors);

bool json_parse_sprinkler_configuration(const char* json_buffer, Sprinkler* sprinkler) {
    int current_token_index;
    TokenVector *tokens = token_vector_new();
    jsmntok_t* current_token;
    size_t number_of_tokens;
    bool ret = true;

    // Parse json string
    if (!json_parse(json_buffer, tokens)) {
        add_to_log("json_parse_sprinkler_configuration: Could not parse json.", ERROR);
        token_vector_destroy(tokens);
        return false;
    }
    
    current_token = token_vector_get_pointer(tokens, 0);
    number_of_tokens = current_token->size;
    if (number_of_tokens <= 0 || current_token->type != JSMN_OBJECT) {
        add_to_log("json_parse_sprinkler_configuration: Could not parse json.", ERROR);
        token_vector_destroy(tokens);
        return false;
    }
    // iterate of all tokens, try to load configuration values
    current_token++;
    for ( current_token_index = 0; current_token_index < number_of_tokens ; ) {
        // Lets find out what to do with the key-
        if (TOKEN_STRING(json_buffer, *current_token, ID_TAG)) { // Id tag
            if (!token_to_int(json_buffer, (current_token+1), &sprinkler->id)) {
                ret = false;
                break;
            }
        } else if (TOKEN_STRING(json_buffer, *current_token, REFRESH_RATE_TAG)) { // Port index tag
            if (!token_to_uint(json_buffer, (current_token+1), &sprinkler->refresh_rate)) {
                ret = false;
                break;
            }
        } else if (TOKEN_STRING(json_buffer, *current_token, MAIN_VALF_DELAY_TAG)) { // Port index tag
            if (!token_to_int(json_buffer, (current_token+1), &sprinkler->main_valf_delay)) {
                ret = false;
                break;
            }
        } else if (TOKEN_STRING(json_buffer, *current_token, MAIN_VALF_TAG)) { // Port index tag
            if (!token_to_int(json_buffer, (current_token+1), &sprinkler->main_valf)) {
                ret = false;
                break;
            }
        } // else - ignore this key.
        current_token_index += 2;
        current_token += 2;
    }
    
    token_vector_destroy(tokens);
    return ret;
}

bool json_parse_sensors(const char* json_buffer, ListElement* sensors) {
    bool ret = true;
    TokenVector *tokens = token_vector_new();
    
    // Parse json string
    if (json_parse(json_buffer, tokens)) {
        if (!json_parse_sensors_internal(tokens, json_buffer, sensors)) {
            add_to_log("json_parse_sensors: Could not find sensors data.", ERROR);
            ret = false;
        }

        if (!json_parse_alarms_internal(tokens, json_buffer, sensors)) {
            add_to_log("json_parse_sensors: Could not find alarms data.", ERROR);
            ret = false;
        }
        
    }
    else {
        add_to_log("json_parse_sensors: Could not parse json.", ERROR);
    }
        
    token_vector_destroy(tokens);
    return ret;
}

bool json_parse_valves(const char* json_buffer, ListElement* valves) {
    TokenVector *tokens = token_vector_new();
    jsmntok_t* current_token;
    size_t number_of_tokens;
    int current_token_index;
    int valf_index;

    // Parse json string
    if (!json_parse(json_buffer, tokens)) {
        add_to_log("json_parse_valves: Could not parse json.", ERROR);
        token_vector_destroy(tokens);
        return false;
    }

    // expected json : [{"id":4,"port_index":1},{"id":6,"port_index":2},{"id":5,"port_index":4}]
    current_token = token_vector_get_pointer(tokens, 0);
    number_of_tokens = current_token->size;
    if (number_of_tokens <= 0 || current_token->type != JSMN_ARRAY) {
        add_to_log("json_parse_valves: Could not parse json.", ERROR);
        token_vector_destroy(tokens);
        return false;
    }
    
    current_token++;
    current_token_index = 1;
    
    // iterate of all tokens, try to build valves
    for (valf_index = 0 ; valf_index < number_of_tokens; valf_index++) {
        const int next_valf_token_index = current_token_index+current_token->size;
        int port_index =-1, id=-1, value;
        if(current_token->type != JSMN_OBJECT ) {
            current_token += current_token->size + 1;
            continue;
        }
        current_token_index++;
        current_token++;
        
        while(current_token_index < next_valf_token_index) {
            const int next_object_token = current_token_index + current_token->size+1;
            if (current_token->type != JSMN_STRING) {// Must be an error...
                current_token_index = next_object_token;
                current_token = token_vector_get_pointer(tokens, current_token_index);
                continue;
            }

            if ((current_token+1)->type != JSMN_PRIMITIVE) {// Must be an error...
                current_token_index = next_object_token;
                current_token = token_vector_get_pointer(tokens, current_token_index);
                continue;
            }

            // Read the value
            if (!token_to_int(json_buffer, current_token+1, &value)) {
                current_token_index = next_object_token;
                current_token = token_vector_get_pointer(tokens, current_token_index);
                continue;
            }

            if (TOKEN_STRING(json_buffer, *current_token, ID_TAG)) { // Id tag
                id = value;
            } else if (TOKEN_STRING(json_buffer, *current_token, PORT_INDEX_TAG)) { // Port index tag
                port_index = value;
            } // else - ignore this key.

            current_token_index += 2;
            current_token += 2;
        }
        
        if(id>=0 && port_index>=0) {
            // Create valf
            Valf* v = valf_create();
            v->id = id;
            v->port_index = port_index;
            list_add(valves, v);
        }
    }
    
    token_vector_destroy(tokens);
    return true;
}

bool json_parse_irrigations(const char* json_buffer, ListElement* irrigations) {
   TokenVector *tokens = token_vector_new();
    jsmntok_t* current_token;
    size_t number_of_tokens;
    int current_token_index;
    int irrigation_index;

    // Parse json string
    if (!json_parse(json_buffer, tokens)) {
        add_to_log("json_parse_irrigations: Could not parse json.", ERROR);
        token_vector_destroy(tokens);
        return false;
    }

    // expected json : [{"start_time":1350339360,"valf_id":4,"irrigation_mode":"time","amount":2}]
    current_token = token_vector_get_pointer(tokens, 0);
    number_of_tokens = current_token->size;
    if (number_of_tokens <= 0 || current_token->type != JSMN_ARRAY) {
        add_to_log("json_parse_irrigations: Could not parse json.", ERROR);
        token_vector_destroy(tokens);
        return false;
    }
    
    current_token++;
    current_token_index = 1;
    
    // iterate of all tokens, try to build valves
    for (irrigation_index = 0 ; irrigation_index < number_of_tokens; irrigation_index++) {
        const int next_irrigation_token_index = current_token_index+current_token->size;
        int number_of_processed_tokens = 0;
        time_t start_time=0;
        int valf_id=-1;
        enum IrrigationModes mode = TIME;
        size_t amount;
        
        if(current_token->type != JSMN_OBJECT ) { // Not an object, skip to the next token.
            current_token += current_token->size + 1;
            continue;
        }
        current_token_index++;
        current_token++;
        
        while(current_token_index < next_irrigation_token_index) {
            const int next_object_token = current_token_index + current_token->size+1;
            if (current_token->type != JSMN_STRING) {// Must be an error...
                current_token_index = next_object_token;
                current_token = token_vector_get_pointer(tokens, current_token_index);
                continue;
            }

            if ((current_token+1)->type == JSMN_PRIMITIVE) {
                int value;
                // Read the value
                if (!token_to_int(json_buffer, current_token+1, &value)) { // Error
                    current_token_index = next_object_token;
                    current_token = token_vector_get_pointer(tokens, current_token_index);
                    continue;
                }

                if (TOKEN_STRING(json_buffer, *current_token, START_TIME_TAG)) {
                    start_time = value;
                    number_of_processed_tokens++;
                } else if (TOKEN_STRING(json_buffer, *current_token, VALF_ID_TAG)) {
                    valf_id = value;
                    number_of_processed_tokens++;
                } else if (TOKEN_STRING(json_buffer, *current_token, AMOUNT_TAG)) {
                    amount = value;
                    number_of_processed_tokens++;
                } // else - ignore this key.
            }
            else if ((current_token+1)->type == JSMN_STRING) {
                if (TOKEN_STRING(json_buffer, *current_token, IRRIGATION_MODE_TAG)) {
                    if (TOKEN_STRING(json_buffer, *(current_token+1), IRRIGATION_MODE_TIME)) {
                        mode = TIME;
                        number_of_processed_tokens++;
                    } else if (TOKEN_STRING(json_buffer, *(current_token+1), IRRIGATION_MODE_VOLUME)) {
                        mode = VOLUME;
                        number_of_processed_tokens++;
                    }
                    // TODO - what to do in case of an error? - currently ignore.
                } // else - ignore this key.
            }
            else { // Error
                current_token_index = next_object_token;
                current_token = token_vector_get_pointer(tokens, current_token_index);
                continue;                
            }

            current_token_index += 2;
            current_token += 2;
        }
        
        if(number_of_processed_tokens >= 4) {
            // Create valf
            Irrigation* i = irrigation_create();
            i->amount = amount;
            i->mode = mode;
            i->start_time = start_time;
            i->valf_id = valf_id;
                    
            list_add(irrigations, i);
        }
    }
    
    token_vector_destroy(tokens);
    return true;    
}

bool json_parse(const char *json_buffer, TokenVector *tokens) {
    int jsmn_ret;
    jsmn_parser p;
    jsmn_init(&p);
    jsmn_ret = jsmn_parse(&p, json_buffer, tokens);
    return (JSMN_SUCCESS == jsmn_ret);
}

int find_json_array_token(TokenVector *tokens, const char* json_buffer, const char* token_key) {
    size_t current_token_index, found_token_index;
    const size_t number_of_tokens = token_vector_size(tokens);
    jsmntok_t* current_token = token_vector_get_pointer(tokens,0);
    for (current_token_index = 0; current_token_index < number_of_tokens; current_token_index++, current_token++) {
        if (current_token->type == JSMN_STRING && TOKEN_STRING(json_buffer, *current_token, token_key)) {
            found_token_index = current_token_index + 1;
            if ((current_token+1)->type != JSMN_ARRAY)
                return -1;
            else
                return found_token_index;
        }
    }
    return -1;
}

bool token_to_int(const char* json_buffer, jsmntok_t *token, int *value) {
    if (token->type != JSMN_PRIMITIVE)
        return false;

    return (sscanf(&json_buffer[token->start], "%d", value) == 1);
}

bool token_to_uint(const char* json_buffer, jsmntok_t *token, size_t *value) {
    if (token->type != JSMN_PRIMITIVE)
        return false;

    return (sscanf(&json_buffer[token->start], "%zu", value) == 1);
    
}
bool token_to_double(const char* json_buffer, jsmntok_t *token, double *value) {
    if (token->type != JSMN_PRIMITIVE)
        return false;

    return (sscanf(&json_buffer[token->start], "%lf", value) == 1);
}

bool token_to_alarm_type(const char* json_buffer, jsmntok_t *token, enum AlarmType *type) {
    const char* buf = &json_buffer[token->start];
    const size_t len = token->end - token->start;

    if (token->type != JSMN_STRING)
        return false;

    if (strncasecmp(buf, "EQUAL", len) == 0) {
        *type = EQUAL;
        return true;
    }
    if (strncasecmp(buf, "NOT_EQUAL", len) == 0) {
        *type = NOT_EQUAL;
        return true;
    }
    if (strncasecmp(buf, "GREATER_THAN", len) == 0) {
        *type = GREATER_THAN;
        return true;
    }
    if (strncasecmp(buf, "LESS_THAN", len) == 0) {
        *type = LESS_THAN;
        return true;
    }

    return false;
}

bool json_parse_sensors_internal(TokenVector* tokens_vector, const char* json_buffer, ListElement* sensors) {
    int sensors_array_token_index, current_token_index, sensor_index;
    jsmntok_t* tokens = token_vector_get_pointer(tokens_vector, 0);

    // Find sensors array token:
    sensors_array_token_index = find_json_array_token(tokens_vector, json_buffer, SENSORS_TAG);
    if (sensors_array_token_index < 0) {
        return false;
    }

    current_token_index = sensors_array_token_index + 1;
    
    // iterate of all tokens, try to build sensors
    for (sensor_index = 0 ; sensor_index < tokens[sensors_array_token_index].size; sensor_index++) {
        int id = -1, port_index = -1, value;
        const unsigned int next_sensor_token_index = current_token_index + tokens[current_token_index].size + 1;

        // We're expecting something like - {"id":4,"port_index":6}
        if (tokens[current_token_index].type != JSMN_OBJECT || tokens[current_token_index].size < 4) {
            current_token_index = next_sensor_token_index;
            continue;
        }

        current_token_index++;

        // First token is the key, the second is the value
        
        while (current_token_index < next_sensor_token_index) {
            const unsigned int next_object_token_index = current_token_index + tokens[current_token_index].size + 1;
            if (tokens[current_token_index].type != JSMN_STRING) { // Must be an error...
                current_token_index = next_object_token_index;
                continue;
            }

            if (tokens[current_token_index + 1].type != JSMN_PRIMITIVE) { // Must be an error...
                current_token_index = next_object_token_index;
                continue;
            }

            // Read the value
            if (!token_to_int(json_buffer, &tokens[current_token_index + 1], &value)) {
                current_token_index = next_object_token_index;
                continue;
            }

            if (TOKEN_STRING(json_buffer, tokens[current_token_index], ID_TAG)) { // Id tag
                id = value;
            } else if (TOKEN_STRING(json_buffer, tokens[current_token_index], PORT_INDEX_TAG)) { // Port index tag
                port_index = value;
            } // else - ignore this key.

            current_token_index += 2;
        }

        if (id >= 0 && port_index >= 0) { // Add sensor
            Sensor* sensor = sensor_create();
            sensor->id = id;
            sensor->port_index = port_index;
            list_add(sensors, sensor);
        }
    }
    return true;
}

bool json_parse_alarms_internal(TokenVector* tokens_vector, const char* json_buffer, ListElement* sensors) {
    int max_port_index = 0;
    int alarm_token_index, current_token_index, alarm_index;
    Sensor** sensors_hash;
    ListElement* root_sensors;
    int sensor_index;
    jsmntok_t* tokens = token_vector_get_pointer(tokens_vector, 0);

    if (list_empty(sensors))
        return true;

    alarm_token_index = find_json_array_token(tokens_vector, json_buffer, ALARM_TAG);
    if (alarm_token_index < 0) { // No alarms, should not be a problem.
        return true;
    }

    if(tokens[alarm_token_index].type != JSMN_ARRAY)
        return false;
    
    // Build sensor hash table - port_index to sensor;
    for (root_sensors = sensors->next; root_sensors != NULL; root_sensors = root_sensors->next) {
        Sensor* sensor = (Sensor*)root_sensors->node;
        if (sensor->port_index < 0)
            return false; // invalid

        if (sensor->port_index > max_port_index)
            max_port_index = sensor->port_index;
    }

    sensors_hash = (Sensor**) calloc(sizeof (Sensor*), max_port_index + 1);
    for (sensor_index = 0; sensor_index <= max_port_index; sensor_index++) // Zero all pointers, could be memset.
        sensors_hash[sensor_index] = NULL;

    for (root_sensors = sensors->next; root_sensors != NULL; root_sensors = root_sensors->next) {
        Sensor* sensor = (Sensor*)root_sensors->node;
        sensors_hash[sensor->port_index] = sensor;
    }

    // iterate of all tokens, try to build alarms
    for (current_token_index = alarm_token_index + 1, alarm_index = 0;
            alarm_index < tokens[alarm_token_index].size; alarm_index++ ) {
        int port_index = -1;
        double alarm_value = -9999;
        enum AlarmType alarm_type = INVALID;
        const size_t number_of_object_tokens = tokens[current_token_index].size;
        const size_t next_alarm_token_index = current_token_index + number_of_object_tokens; 

        // We're expecting something like - {"port_index":1,"alarm_value":5.0,"condition_type":"greater_than"}
        if (tokens[current_token_index].type != JSMN_OBJECT || number_of_object_tokens < 6) {
            current_token_index = next_alarm_token_index;
            continue; // TODO - add logs
        }

        current_token_index++;

        // First token is the key, the second is the value
        while (current_token_index < next_alarm_token_index) {
            const unsigned int next_object_token_index = current_token_index + tokens[current_token_index].size + 1;
            if (tokens[current_token_index].type != JSMN_STRING) {// Must be an error...
                current_token_index = next_object_token_index;
                continue;
            }

            if (tokens[current_token_index + 1].type != JSMN_PRIMITIVE
                    && tokens[current_token_index + 1].type != JSMN_STRING) {// Must be an error...
                current_token_index = next_object_token_index;
                continue;
            }

            if (TOKEN_STRING(json_buffer, tokens[current_token_index], ALARM_VALUE_TAG)) { // alarm value tag
                if (!token_to_double(json_buffer, &tokens[current_token_index + 1], &alarm_value)) {
                    current_token_index = next_alarm_token_index;
                    break;
                }
            } else if (TOKEN_STRING(json_buffer, tokens[current_token_index], PORT_INDEX_TAG)) { // Port index tag
                if (!token_to_int(json_buffer, &tokens[current_token_index + 1], &port_index)) {
                    current_token_index = next_alarm_token_index;
                    break;
                }
            } else if (TOKEN_STRING(json_buffer, tokens[current_token_index], CONDITION_TYPE_TAG)) { // Condition type tag
                if (!token_to_alarm_type(json_buffer, &tokens[current_token_index + 1], &alarm_type)) {
                    current_token_index = next_alarm_token_index;
                    break;
                }
            } // else - ignore this key.

            current_token_index += 2;
        }

        if (port_index >= 0 && alarm_type != INVALID && alarm_value != -9999 && port_index <= max_port_index) { // Add alarm
            Alarm* alarm = alarm_create(alarm_value, alarm_type);
            Sensor* s = sensors_hash[port_index];
            if(s!=NULL)
                list_add(s->alarms, (void*)alarm);
            else
                alarm_delete(alarm);
        }
    }


    free(sensors_hash);

    return true;
}
