/*
 * File:   test_json_formatter.c
 * Author: supox
 *
 * Created on Sep 27, 2012, 9:06:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sensor.h"
#include "json_formatter.h"

/*
 * Simple C Test Suite
 */

void test_format_sensors() {
    char message[256];
    Sensor sensors[2];
    sensors[0].last_reading_value = 1;
    sensors[0].port_index = 2;
    sensors[1].last_reading_value = 3;
    sensors[1].port_index = 4;
    
    assert(json_format_sensors(message, 256, sensors, 2));
    assert(strcmp(message, "[{\"port\":2, \"value\":1},{\"port\":4, \"value\":3}]")==0);    
}

void test_format_sensors_overflow() {
    char message[256];
    const int iNumberOfSensors = 30;
    int iIndex;
    Sensor sensors[iNumberOfSensors];
    for(iIndex = 0 ; iIndex < iNumberOfSensors ; iIndex++)
    {
        sensors[iIndex].last_reading_value = 1;
        sensors[iIndex].port_index = 2;
    }
    
    assert(!json_format_sensors(message, 256, sensors, iNumberOfSensors));
    
}



int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_json_formatter\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test_format_sensors (test_json_formatter)\n");
    test_format_sensors();
    printf("%%TEST_FINISHED%% time=0 test1 (test_json_formatter) \n");

    printf("%%TEST_STARTED%% test_format_sensors_overflow (test_json_formatter)\n");
    test_format_sensors_overflow();
    printf("%%TEST_FINISHED%% time=0 test_format_sensors_overflow (test_json_formatter) \n");
    
    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
