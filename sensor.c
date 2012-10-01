#include "sensor.h"
#include "time_functions.h"
#include "config.h"
#include "reading_data.h"
#include "alarm.h"

#include <stdio.h>
#include <stdlib.h>

static bool sensor_add_reading_if_needed(Sensor *s, const bool will_alarm);

bool sensor_get_reading(Sensor* s, double* value, bool *will_alarm) {
    bool ret = s->read_sensor(s, value);
    if (ret) {
        s->last_reading_value = *value;
        s->last_reading_time = get_time();
        *will_alarm = alarm_list_will_alarm(s->alarms, s->last_reading_value);
        ret = sensor_add_reading_if_needed(s, *will_alarm);
    }
    return ret;
}


bool sensor_add_reading_if_needed(Sensor *s, const bool will_alarm) {
    if(will_alarm || s->last_reading_time > s->last_saved_reading_time + s->report_reading_time_delta) {
        // Save reading to queue:
        reading_data* data = reading_data_create(s->last_reading_time, s->last_reading_value);
        list_add(s->readings_to_report, (void*)data);
        s->last_saved_reading_time = s->last_reading_time;
    }
    return true;
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
    s->last_saved_reading_time = 0;
    s->report_reading_time_delta = DEFAULT_SENSOR_READING_TIME_DELTA_SECONDS;
    s->type = type;
    s->alarms = alarm_list_create();
    s->readings_to_report = list_create();
    return sensor_factory_init(s);
}

void sensor_delete(Sensor* s) {
    sensor_free_elements(s);
    free(s);
}

void sensor_free_elements(Sensor* s) {
    list_delete(s->alarms);
    list_delete(s->readings_to_report);
}

ListElement* sensor_create_list() {
    ListElement *root = list_create();
    list_set_delete_function(root, (delete_function)sensor_delete);
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
