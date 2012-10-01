/* 
 * File:   json_parser.h
 * Author: supox
 *
 * Created on September 29, 2012, 4:50 PM
 */

#ifndef JSON_PARSER_H
#define	JSON_PARSER_H
#include <stdbool.h>
#include "sensor.h"
#include "sprinkler.h"

bool json_parse_sensors(const char* json_buffer, ListElement* sensors);
bool json_parse_sprinkler_configuration(const char* json_buffer, Sprinkler* sprinkler);

#endif	/* JSON_PARSER_H */

