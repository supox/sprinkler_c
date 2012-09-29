#include "json_formatter.h"
#include "logger.h"
#include <stdio.h>

bool json_format_sensors(char* message, size_t max_length, Sensor* sensors, size_t number_of_sensors) {
    char *message_ptr = message;
    const size_t iMinMessageSize = 10;
    bool first = true;
    int iSensorIndex;
    message_ptr += sprintf(message_ptr, "[");
    for(iSensorIndex = 0 ; iSensorIndex < number_of_sensors ; iSensorIndex++) {
        if(!first)
            message_ptr += sprintf(message_ptr, ",");
        message_ptr += sprintf(message_ptr, "{\"port\":%d, \"value\":%.0lf}",
                sensors[iSensorIndex].port_index,
                sensors[iSensorIndex].last_reading_value);
        first = false;
        
        if( (int)(message_ptr - message) > max_length - iMinMessageSize) {
            add_to_log("json_format_sensors - buffer too small", ERROR);
            return false;
        }
    }
    message_ptr += sprintf(message_ptr, "]");
    
    return true;
    
}
