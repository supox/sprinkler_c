#include "alarm.h"
#include <stdlib.h>

bool alarm_will_alarm(Alarm *alarm, const double sensor_value) {
    switch(alarm->type) {
        case EQUAL :
            return alarm->alarm_value == sensor_value;
        case NOT_EQUAL :
            return alarm->alarm_value != sensor_value;
        case GREATER_THAN :
            return alarm->alarm_value > sensor_value;
        case LESS_THAN :
            return alarm->alarm_value < sensor_value;
        default:
            return false;
    }
}

Alarm* alarm_create(double alarm_value, enum AlarmType type) {
    Alarm* alarm = (Alarm*)malloc(sizeof(Alarm));
    if(alarm != NULL) {
        alarm->alarm_value = alarm_value;
        alarm->type = type;
    }
    return alarm;
}

void alarm_delete(Alarm* alarm) {
    free(alarm);
}

