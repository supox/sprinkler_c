#include "sensor.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool sensor_get_reading(Sensor* s, double* value)
{
    switch(s->type)
    {
        case MOCK:
             // generate a number between 1 to 10
            *value = (double)(rand() % 10 + 1);
            return true;
            break;
        default:
            // TODO !!!
            break;
    }
    return false;    
}

Sensor* sensor_create() {
    Sensor* s = (Sensor*)malloc(sizeof(Sensor));
    s->port_index=0;
    s->last_reading_value=0;
    s->last_reading_time=0;
    s->type = MOCK;
    return s;
}
void sensor_delete(Sensor* s){
    free(s);
}

