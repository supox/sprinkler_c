/*
 * File:   test_sensor.c
 * Author: supox
 *
 * Created on Sep 25, 2012, 2:41:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sensor.h"
#include "alarm.h"
/*
 * Simple C Test Suite
 */

void test_sensor() {
    Sensor* s;
    double value=-1;
    int i;
    bool will_alarm = false;
    printf("test_sensor test 1\n");
    
    s = sensor_create();
    assert(s);
    
    assert(sensor_get_reading(s, &value, &will_alarm));
    assert(value!=-1);
    assert(!will_alarm);
    
    // Make sure that the reading is stored:
    assert(list_count(s->readings_to_report)==1);
    
    // Check alarms
    Alarm *alarm = alarm_create(-1000, NOT_EQUAL);
    list_add(s->alarms, alarm);
    assert(sensor_get_reading(s, &value, &will_alarm));
    assert(will_alarm);

    // Make sure that the reading is stored due to alarm:
    assert(list_count(s->readings_to_report)==2);
    list_remove(s->alarms,alarm);
    
    // do several reading, make sure they are not stored.
    list_clear(s->readings_to_report);
    for(i=0;i<10;i++) {
        assert(sensor_get_reading(s, &value, &will_alarm));
        assert(list_count(s->readings_to_report)==0);
    }
    
    // Make sure reading cause to report if the enough time passed.
    list_clear(s->readings_to_report);
    s->last_saved_reading_time = get_time() - s->report_reading_time_delta-1;
    assert(sensor_get_reading(s, &value, &will_alarm));
    assert(list_count(s->readings_to_report)==1);

    // Make sure reading not issue report if not enough time passed.
    list_clear(s->readings_to_report);
    s->last_saved_reading_time = get_time() - s->report_reading_time_delta+1;
    assert(sensor_get_reading(s, &value, &will_alarm));
    assert(list_count(s->readings_to_report)==0);
    
    sensor_delete(s);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_sensor\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test_sensor)\n");
    test_sensor();
    printf("%%TEST_FINISHED%% time=0 test1 (test_sensor) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
