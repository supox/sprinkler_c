#include "json_parser.h"
#include "jsmn.h"
#include "config.h"
#include "logger.h"
#include <stdio.h>
#include <string.h>

#define SENSORS_TAG             "sensors"
#define ID_TAG                  "id"
#define PORT_INDEX_TAG          "port_index"
#define MAX_NUMBER_OF_TOKENS    100

#define TOKEN_STRING(js, t, s) \
	(strncmp(js+(t).start, s, (t).end - (t).start) == 0 \
	 && strlen(s) == (t).end - (t).start)

bool json_parse(const char *json_buffer, jsmntok_t *tokens);
int find_json_array_token(jsmntok_t *tokens, const char* json_buffer, const char* token_key);

bool json_parse_sensors(const char* json_buffer, Sensor sensors[], size_t* iSensorsLength, size_t MaxSensorsLength) {
    // Parse json:
    int num_of_sensors = 0;
    int iSensorsArrayTokenIndex, iCurrentTokenIndex;
    jsmntok_t tokens[MAX_NUMBER_OF_TOKENS];

    // Parse json string
    if (!json_parse(json_buffer, tokens)) {
        add_to_log("json_parse_sensors: Could not parse json.", ERROR);
        return false;
    }

    // Find sensors array token:
    iSensorsArrayTokenIndex = find_json_array_token(tokens, json_buffer, SENSORS_TAG);
    if (iSensorsArrayTokenIndex < 0) {
        add_to_log("json_parse_sensors: Could not find sensors data.", ERROR);
        return false;
    }

    // iterate of all tokens, try to build sensors
    for (iCurrentTokenIndex = iSensorsArrayTokenIndex + 1;
            tokens[iCurrentTokenIndex].start < tokens[iSensorsArrayTokenIndex].end;
            ) {
        int id = -1, port_index = -1, value;

        // We're expecting something like - {"id":4,"port_index":6}
        if (tokens[iCurrentTokenIndex].type != JSMN_OBJECT || tokens[iCurrentTokenIndex].size < 4) {
            break; // TODO - add logs
        }

        iCurrentTokenIndex++;

        // First token is the key, the second is the value
        while ((id < 0 || port_index < 0) && iCurrentTokenIndex < MAX_NUMBER_OF_TOKENS) {
            if (tokens[iCurrentTokenIndex].type != JSMN_STRING) // Must be an error...
                break;

            if (tokens[iCurrentTokenIndex + 1].type != JSMN_PRIMITIVE) // Must be an error...
                break;

            // Read the value
            if (sscanf(&json_buffer[tokens[iCurrentTokenIndex + 1].start], "%d", &value) != 1)
                break;

            if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], ID_TAG)) { // Id tag
                id = value;
            } else if (TOKEN_STRING(json_buffer, tokens[iCurrentTokenIndex], PORT_INDEX_TAG)) { // Port index tag
                port_index = value;
            } // else - ignore this key.

            iCurrentTokenIndex += 2;

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