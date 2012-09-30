#include "json_formatter.h"
#include "logger.h"
#include <stdio.h>

bool json_format_sensors(char* message, size_t max_length, Sensor* sensors, size_t number_of_sensors) {
    char *message_ptr = message;
    bool first = true;
    int iSensorIndex, iBytesWritten;

    // Write prefix
    iBytesWritten = snprintf(message_ptr, max_length, "[");
    if (iBytesWritten > max_length)
        return false;
    message_ptr += iBytesWritten;
    max_length -= iBytesWritten;

    for (iSensorIndex = 0; iSensorIndex < number_of_sensors; iSensorIndex++) {
        if (!first) {
            // Write comma
            iBytesWritten = snprintf(message_ptr, max_length, ",");
            if (iBytesWritten > max_length)
                return false;
            message_ptr += iBytesWritten;
            max_length -= iBytesWritten;
        } else
            first = false;

        // Write sensor data
        iBytesWritten = snprintf(message_ptr, max_length, "{\"port\":%d, \"value\":%.0lf}",
                sensors[iSensorIndex].port_index,
                sensors[iSensorIndex].last_reading_value);
        if (iBytesWritten > max_length)
            return false;
        message_ptr += iBytesWritten;
        max_length -= iBytesWritten;
    }

    // Write suffix
    iBytesWritten = snprintf(message_ptr, max_length, "]");
    if (iBytesWritten > max_length)
        return false;
    message_ptr += iBytesWritten;
    max_length -= iBytesWritten;

    return true;

}
