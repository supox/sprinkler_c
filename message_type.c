#include "message_type.h"
#include <stdio.h>

void message_type_to_string(enum message_type message, char str[])
{
    switch(message)
    {
        case LOG:
            sprintf(str,"LOG");
            break;
        case SENSOR_READING:
            sprintf(str,"SENSOR_READING");
            break;
        case GENERAL_MESSAGE: default:
            sprintf(str,"GENERAL_MESSAGE");
            break;
    }
}
