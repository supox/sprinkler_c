
/* 
 * File:   sensor.h
 * Author: supox
 *
 * Created on September 24, 2012, 11:59 PM
 */

#ifndef SENSOR_H
#define	SENSOR_H

#include "sensor_type.h"
#include "alarm_list.h"
#include <stdbool.h>
#include <time.h>


struct SensorStruct;

struct SensorStruct {
    int id;
    int port_index;
    double last_reading_value;
    time_t last_reading_time;
    enum sensor_type type;
    AlarmList* alarms;
    bool (*read_sensor)(struct SensorStruct *this);
};

typedef struct SensorStruct Sensor;

bool sensor_get_reading(Sensor* s, double* value, bool* will_alarm);

Sensor* sensor_create();
bool sensor_init(Sensor* s, enum sensor_type type);
void sensor_delete(Sensor*);
Sensor** sensor_create_array(const size_t length);
void sensor_delete_array(Sensor** sensors, const size_t length);

#endif	/* SENSOR_H */
