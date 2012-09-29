/* 
 * File:   json_formatter.h
 * Author: supox
 *
 * Created on September 27, 2012, 9:01 PM
 */

#ifndef JSON_FORMATTER_H
#define	JSON_FORMATTER_H

#include <stdbool.h>
#include "sensor.h"

bool json_format_sensors(char* buf, size_t max_length, Sensor* sensors, size_t number_of_sensors);

#endif	/* JSON_FORMATTER_H */

