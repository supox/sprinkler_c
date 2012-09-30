/* 
 * File:   alarm.h
 * Author: supox
 *
 * Created on September 30, 2012, 10:45 PM
 */

#ifndef ALARM_H
#define	ALARM_H

#include "alarm_type.h"
#include <stdbool.h>

typedef struct {
    double alarm_value;
    enum AlarmType type;
} Alarm;


bool alarm_will_alarm(Alarm *alarm, const double sensor_value);

// Constructor and destructor
Alarm* alarm_create(double alarm_value, enum AlarmType type);
void alarm_delete(Alarm* alarm);

#endif	/* ALARM_H */

