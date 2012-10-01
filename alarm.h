/* 
 * File:   alarm.h
 * Author: supox
 *
 * Created on September 30, 2012, 10:45 PM
 */

#ifndef ALARM_H
#define	ALARM_H

#include "alarm_type.h"
#include "linked_list.h"
#include <stdbool.h>

typedef struct {
    double alarm_value;
    enum AlarmType type;
} Alarm;


bool alarm_will_alarm(Alarm *alarm, const double sensor_value);
bool alarm_list_will_alarm(ListElement *root, const double sensor_value);

// Constructor and destructor
ListElement* alarm_list_create();
Alarm* alarm_create(double alarm_value, enum AlarmType type);
void alarm_delete(Alarm* alarm);

#endif	/* ALARM_H */

