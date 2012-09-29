
/* 
 * File:   sensor.h
 * Author: supox
 *
 * Created on September 24, 2012, 11:59 PM
 */

#ifndef SENSOR_H
#define	SENSOR_H

#include <stdbool.h>
#include <time.h>
#include "sensor_type.h"

struct SensorStruct;

typedef struct {
    int port_index;
    double last_reading_value;
    time_t last_reading_time;
    enum sensor_type type;
} Sensor;

bool sensor_get_reading(Sensor* s, double* value);

Sensor* sensor_create();
void sensor_init(Sensor* s);
void sensor_delete(Sensor*);

#endif	/* SENSOR_H */
