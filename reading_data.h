/* 
 * File:   sensor_reading_data.h
 * Author: supox
 *
 * Created on October 1, 2012, 9:25 PM
 */

#ifndef READING_DATA_H
#define	READING_DATA_H

#include <time.h>

typedef struct {
    time_t reading_time;
    double reading_value;
} ReadingData;

ReadingData* reading_data_create(const time_t time, const double value);
void reading_data_destroy(ReadingData* data);

#endif	/* SENSOR_READING_DATA_H */

