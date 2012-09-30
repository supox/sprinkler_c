/* 
 * File:   alarm_list.h
 * Author: supox
 *
 * Created on September 30, 2012, 10:54 PM
 */

#ifndef ALARM_LIST_H
#define	ALARM_LIST_H

#include "alarm.h"

struct AlarmListStruct{
    Alarm* node;
    struct AlarmListStruct* next;
};

typedef struct AlarmListStruct AlarmList;

bool alarm_list_will_alarm(AlarmList *root, const double sensor_value);

// List functions
bool alarm_list_add(AlarmList* root, Alarm* node);
bool alarm_list_contains(AlarmList* root, Alarm* node);
bool alarm_list_remove(AlarmList* root, Alarm *node);
AlarmList* alarm_list_create();
bool alarm_list_delete(AlarmList* root);

#endif	/* ALARM_LIST_H */

