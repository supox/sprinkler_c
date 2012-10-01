#include "json_parser.h"
#include "jsmn.h"
#include "config.h"
#include "logger.h"
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

#define TOKEN_STRING(js, t, s) \
	(strncmp(js+(t).start, s, (t).end - (t).start) == 0 \
	 && strlen(s) == (t).end - (t).start)

static bool json_parse(const char *json_buffer, jsmntok_t *tokens);
static int find_json_array_token(jsmntok_t *tokens, const char* json_buffer, const char* token_key);
static bool token_to_int(const char* json_buffer, jsmntok_t *token, int *value);
static bool token_to_double(const char* json_buffer, jsmntok_t *token, double *value);
static bool json_parse_sensors_int(jsmntok_t* tokens, const char* json_buffer, Sensor sensors[], size_t* iSensorsLength, size_t MaxSensorsLength);
static bool json_parse_alarms_int(jsmntok_t* tokens, const char* json_buffer, Sensor sensors[], size_t iSensorsLength);

bool json_parse_sprinkler_configuration(const char* json_buffer, Sprinkler* sprinkler) {
    int iCurrentTokenIndex;
    jsmntok_t tokens[MAX_NUMBER_OF_TOKENS];

    // Parse json string
    if (!json_parse(json_buffer, tokens)) {
        add_to_log("json_parse_sprinkler_configuration: Could not parse json.", ERROR);
        return false;
    }

    if (tokens[0].size <= 0 || tokens[0].type != JSMN_OBJECT) {
        add_to_log("json_parse_sprinkler_configuration: Could not parse json.", ERROR);
        return false;
    }
    // iterate of all tokens, try to load configuration values
    for (iCurrentTokenIndex = 1;
            iCurrentTokenIndex < tokens[0].size + 1 &&
            tokens[iCurrentTokenIndex].start > tokens[0].start &&
            tokens[iCurrentTokenIndex].end < tokens[0].end;
            ) {

        // Lets find out what to do with the key-
        if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], ID_TAG)) { // Id tag
            if (!token_to_int(json_buffer, &tokens[iCurrentTokenIndex + 1], &sprinkler->id))
                return false;
        } else if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], REFRESH_RATE_TAG)) { // Port index tag
            if (!token_to_int(json_buffer, &tokens[iCurrentTokenIndex + 1], &sprinkler->refresh_rate))
                return false;
        } else if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], MAIN_VALF_DELAY_TAG)) { // Port index tag
            if (!token_to_int(json_buffer, &tokens[iCurrentTokenIndex + 1], &sprinkler->main_valf_delay))
                return false;
        } else if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], MAIN_VALF_TAG)) { // Port index tag
            if (!token_to_int(json_buffer, &tokens[iCurrentTokenIndex + 1], &sprinkler->main_valf))
                return false;
        } // else - ignore this key.
        iCurrentTokenIndex += 2;
    }
}

bool json_parse_sensors(const char* json_buffer, Sensor sensors[], size_t* iSensorsLength, size_t MaxSensorsLength) {
    jsmntok_t tokens[MAX_NUMBER_OF_TOKENS];

    // Parse json string
    if (!json_parse(json_buffer, tokens)) {
        add_to_log("json_parse_sensors: Could not parse json.", ERROR);
        return false;
    }

    if (!json_parse_sensors_int(tokens, json_buffer, sensors, iSensorsLength, MaxSensorsLength)) {
        add_to_log("json_parse_sensors: Could not find sensors data.", ERROR);
        return false;
    }

    if (!json_parse_alarms_int(tokens, json_buffer, sensors, *iSensorsLength)) {
        add_to_log("json_parse_sensors: Could not find alarms data.", ERROR);
        return false;
    }
    return true;
}

bool json_parse(const char *json_buffer, jsmntok_t *tokens) {
    int jsmn_ret;
    jsmn_parser p;
    jsmn_init(&p);
    jsmn_ret = jsmn_parse(&p, json_buffer, tokens, MAX_NUMBER_OF_TOKENS);
    return (jsmn_ret == JSMN_SUCCESS);
}

int find_json_array_token(jsmntok_t *tok, const char* json_buffer, const char* token_key) {
    int iTokenIndex, iSensorsArrayTokenIndex;
    for (iTokenIndex = 0; iTokenIndex < MAX_NUMBER_OF_TOKENS; iTokenIndex++) {
        if (tok[iTokenIndex].type == JSMN_STRING && TOKEN_STRING(json_buffer, tok[iTokenIndex], token_key)) {
            iSensorsArrayTokenIndex = iTokenIndex + 1;
            if (tok[iSensorsArrayTokenIndex].type != JSMN_ARRAY)
                return -1;
            else
                return iSensorsArrayTokenIndex;
        }
    }
    return -1;
}

bool token_to_int(const char* json_buffer, jsmntok_t *token, int *value) {
    if (token->type != JSMN_PRIMITIVE)
        return false;

    return (sscanf(&json_buffer[token->start], "%d", value) == 1);
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

bool json_parse_sensors_int(jsmntok_t* tokens, const char* json_buffer, Sensor sensors[], size_t* iSensorsLength, size_t MaxSensorsLength) {
    int num_of_sensors = 0;
    int iSensorsArrayTokenIndex, iCurrentTokenIndex;

    // Find sensors array token:
    iSensorsArrayTokenIndex = find_json_array_token(tokens, json_buffer, SENSORS_TAG);
    if (iSensorsArrayTokenIndex < 0) {
        return false;
    }

    // iterate of all tokens, try to build sensors
    for (iCurrentTokenIndex = iSensorsArrayTokenIndex + 1;
            tokens[iCurrentTokenIndex].end < tokens[iSensorsArrayTokenIndex].end;
            ) {
        int id = -1, port_index = -1, value;
        const size_t number_of_object_tokens = tokens[iCurrentTokenIndex].size;
        size_t number_of_processed_tokens = 0; 

        // We're expecting something like - {"id":4,"port_index":6}
        if (tokens[iCurrentTokenIndex].type != JSMN_OBJECT || number_of_object_tokens < 4) {
            continue; // TODO - add logs
        }

        iCurrentTokenIndex++;

        // First token is the key, the second is the value
        while ((id < 0 || port_index < 0) && number_of_processed_tokens < number_of_object_tokens) {
            if (tokens[iCurrentTokenIndex].type != JSMN_STRING) // Must be an error...
                break;

            if (tokens[iCurrentTokenIndex + 1].type != JSMN_PRIMITIVE) // Must be an error...
                break;

            // Read the value
            if (!token_to_int(json_buffer, &tokens[iCurrentTokenIndex + 1], &value))
                break;

            if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], ID_TAG)) { // Id tag
                id = value;
            } else if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], PORT_INDEX_TAG)) { // Port index tag
                port_index = value;
            } // else - ignore this key.

            iCurrentTokenIndex += 2;
            number_of_processed_tokens += 2;
        }

        if (id >= 0 && port_index >= 0) { // Add sensor
            sensors[num_of_sensors].id = id;
            sensors[num_of_sensors].port_index = port_index;

            num_of_sensors++;
            if (num_of_sensors >= MaxSensorsLength)
                break;
        }
    }

    *iSensorsLength = num_of_sensors;
    return true;
}

bool json_parse_alarms_int(jsmntok_t* tokens, const char* json_buffer, Sensor sensors[], size_t iSensorsLength) {
    int max_port_index = 0;
    int iAlarmsTokenIndex, iCurrentTokenIndex;
    size_t sensor_index;
    Sensor** sensors_hash;

    if (iSensorsLength == 0)
        return true;

    iAlarmsTokenIndex = find_json_array_token(tokens, json_buffer, ALARM_TAG);
    if (iAlarmsTokenIndex < 0) { // No alarms, should not be a problem.
        return true;
    }

    // Build sensor hash table - port_index to sensor;
    for (sensor_index = 0; sensor_index < iSensorsLength; sensor_index++) {
        if (sensors[sensor_index].port_index < 0)
            return false; // invalid

        if (sensors[sensor_index].port_index > max_port_index)
            max_port_index = sensors[sensor_index].port_index;
    }

    sensors_hash = (Sensor**) calloc(sizeof (Sensor*), max_port_index + 1);
    for (sensor_index = 0; sensor_index <= max_port_index; sensor_index++) // Zero all pointers, could be memset.
        sensors_hash[sensor_index] = NULL;

    for (sensor_index = 0; sensor_index < iSensorsLength; sensor_index++) { // Build hash
        sensors_hash[sensors[sensor_index].port_index] = &sensors[sensor_index];
    }

    // iterate of all tokens, try to build alarms
    for (iCurrentTokenIndex = iAlarmsTokenIndex + 1;
            tokens[iCurrentTokenIndex].end < tokens[iAlarmsTokenIndex].end;
            ) {
        int port_index = -1;
        double alarm_value = -9999;
        enum AlarmType alarm_type = INVALID;
        const size_t number_of_object_tokens = tokens[iCurrentTokenIndex].size;
        size_t number_of_processed_tokens = 0; 

        // We're expecting something like - {"port_index":1,"alarm_value":5.0,"condition_type":"greater_than"}
        if (tokens[iCurrentTokenIndex].type != JSMN_OBJECT || number_of_object_tokens < 6) {
            iCurrentTokenIndex++;
            continue; // TODO - add logs
        }

        iCurrentTokenIndex++;

        // First token is the key, the second is the value
        while ((port_index < 0 || alarm_type == INVALID || alarm_value == -9999 )
                && number_of_processed_tokens < number_of_object_tokens) {
            if (tokens[iCurrentTokenIndex].type != JSMN_STRING) // Must be an error...
                break;

            if (tokens[iCurrentTokenIndex + 1].type != JSMN_PRIMITIVE
                    && tokens[iCurrentTokenIndex + 1].type != JSMN_STRING) // Must be an error...
                break;

            if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], ALARM_VALUE_TAG)) { // alarm value tag
                if (!token_to_double(json_buffer, &tokens[iCurrentTokenIndex + 1], &alarm_value))
                    break;
            } else if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], PORT_INDEX_TAG)) { // Port index tag
                if (!token_to_int(json_buffer, &tokens[iCurrentTokenIndex + 1], &port_index))
                    break;
            } else if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], CONDITION_TYPE_TAG)) { // Condition type tag
                if (!token_to_alarm_type(json_buffer, &tokens[iCurrentTokenIndex + 1], &alarm_type))
                    break;
            } // else - ignore this key.

            iCurrentTokenIndex += 2;
            number_of_processed_tokens+=2;
        }

        if (port_index >= 0 && alarm_type != INVALID && alarm_value != -9999 && port_index <= max_port_index) { // Add alarm
            Alarm* alarm = alarm_create(alarm_value, alarm_type);
            Sensor* s = sensors_hash[port_index];
            if(s!=NULL)
                alarm_list_add(s->alarms, alarm);
            else
                alarm_delete(alarm);
        }
    }


    free(sensors_hash);

    return true;
}