/*
 * File:   alarm_test.c
 * Author: supox
 *
 * Created on Sep 30, 2012, 11:32:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "alarm.h"

/*
 * Simple C Test Suite
 */

void testAlarm_will_alarm() {
    bool result;
    Alarm* alarm = alarm_create(1, GREATER_THAN);
    double sensor_value;
    
    alarm->type=GREATER_THAN;
    sensor_value = alarm->alarm_value-1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(result);
    sensor_value = alarm->alarm_value+1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(!result);

    alarm->type=LESS_THAN;
    sensor_value = alarm->alarm_value-1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(!result);
    sensor_value = alarm->alarm_value+1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(result);

    alarm->type=EQUAL;
    sensor_value = alarm->alarm_value-1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(!result);
    sensor_value = alarm->alarm_value;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(result);
    sensor_value = alarm->alarm_value+1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(!result);

    alarm->type=NOT_EQUAL;
    sensor_value = alarm->alarm_value-1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(result);
    sensor_value = alarm->alarm_value;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(!result);
    sensor_value = alarm->alarm_value+1;
    result = alarm_will_alarm(alarm, sensor_value);
    assert(result);
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% alarm_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testAlarm_will_alarm (alarm_test)\n");
    testAlarm_will_alarm();
    printf("%%TEST_FINISHED%% time=0 testAlarm_will_alarm (alarm_test)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
