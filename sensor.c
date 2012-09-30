#include "sensor.h"
#include "alarm_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool sensor_get_reading(Sensor* s, double* value, bool *will_alarm) {
    bool ret = s->read_sensor(s);
    if (ret) {
        s->last_reading_time = time(NULL);
        *value = s->last_reading_value;
        *will_alarm = alarm_list_will_alarm(s->alarms, s->last_reading_value);
    }
    return ret;
}

Sensor* sensor_create() {
    Sensor* s = (Sensor*) malloc(sizeof (Sensor));
    if (s != NULL) {
        if (!sensor_init(s, MOCK)) {
            free(s);
            return NULL;
        }
    }
    return s;
}

bool sensor_init(Sensor* s, enum sensor_type type) {
    s->id = 0;
    s->port_index = 0;
    s->last_reading_value = 0;
    s->last_reading_time = 0;
    s->type = type;
    s->alarms = alarm_list_create();
    return sensor_factory_init(s);
}

void sensor_delete(Sensor* s) {
    alarm_list_delete(s->alarms);
    free(s);
}

Sensor** sensor_create_array(const size_t length) {
    Sensor** sa = (Sensor**) calloc(length, sizeof (Sensor*));
    if (sa) {
        size_t i;
        for (i = 0; i < length; i++)
            sa[i] = sensor_create();
    }
    return sa;

}

void sensor_delete_array(Sensor** sensors, const size_t length) {
    size_t i;
    for (i = 0; i < length; i++)
        sensor_delete(sensors[i]);
    free(sensors);
}
