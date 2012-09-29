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
            break;
        default:
            // TODO !!!
            return false;
            break;
    }
    
    s->last_reading_time = time(0);
    s->last_reading_value = *value;
    
    return true;
}

Sensor* sensor_create() {
    Sensor* s = (Sensor*)malloc(sizeof(Sensor));
    sensor_init(s);
    return s;
}

void sensor_init(Sensor* s) {
    s->id=0;
    s->port_index=0;
    s->last_reading_value=0;
    s->last_reading_time=0;
    s->type = MOCK;
}

void sensor_delete(Sensor* s){
    free(s);
}

Sensor** sensor_create_array(const size_t length) {
    Sensor** sa = (Sensor**)calloc(length, sizeof(Sensor*));
    if(sa) {
        int i;
        for(i=0; i<length;i++)
            sa[i] = sensor_create();
    }
    return sa;

}

void sensor_delete_array(Sensor** sensors, const size_t length) {
    int i;
    for(i=0; i<length; i++)
        sensor_delete(sensors[i]);
    free(sensors);
}