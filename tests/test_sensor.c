/*
 * File:   test_sensor.c
 * Author: supox
 *
 * Created on Sep 25, 2012, 2:41:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "sensor.h"
#include <assert.h>
/*
 * Simple C Test Suite
 */

void test1() {
    Sensor* s;
    double value=-1;
    bool will_alarm = false;
    printf("test_sensor test 1\n");
    
    s = sensor_create();
    assert(s);
    
    assert(sensor_get_reading(s, &value, &will_alarm));
    assert(value!=-1);

    sensor_delete(s);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_sensor\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test_sensor)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (test_sensor) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
