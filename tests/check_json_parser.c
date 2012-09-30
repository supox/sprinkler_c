/*
 * File:   check_json_parse.c
 * Author: supox
 *
 * Created on Sep 29, 2012, 4:52:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "json_parser.h"
#include "config.h"

/*
 * Simple C Test Suite
 */

void test_json_parse_sensors() {
    int ids[]={1,2,5,4,6};
    int ports[]={1,2,5,6,8};
    int i;
    const char* json_buffer = "{\"sensors\":[{\"id\":1,\"port_index\":1},{\"id\":2,\"port_index\":2},{\"id\":5,\"port_index\":5},{\"id\":4,\"port_index\":6},{\"id\":6,\"port_index\":8}],\"alarms\":[{\"port_index\":1,\"alarm_value\":5.0,\"condition_type\":\"greater_than\"},{\"port_index\":1,\"alarm_value\":3.0,\"condition_type\":\"not_equal\"},{\"port_index\":1,\"alarm_value\":80.0,\"condition_type\":\"greater_than\"}]}\n";
    Sensor pSensors[MAX_NUMBER_OF_SENSORS];
    bool result;
    size_t iSensorsLength = 0;
    
    for(i = 0; i < MAX_NUMBER_OF_SENSORS ; i++)
        sensor_init(&pSensors[i], MOCK);
    
    result = json_parse_sensors(json_buffer, pSensors, &iSensorsLength, MAX_NUMBER_OF_SENSORS);
    assert(result);
    assert(iSensorsLength == 5);
    for(i=0; i<iSensorsLength; i++) {
        assert(pSensors[i].port_index==ports[i]);
        assert(pSensors[i].id==ids[i]);
    }
}

void test_json_parse_alarms() {
    double values[]={5,3,80};
    enum AlarmType types[] = {GREATER_THAN, NOT_EQUAL, GREATER_THAN};
    int i;
    const char* json_buffer = "{\"sensors\":[{\"id\":1,\"port_index\":1},{\"id\":2,\"port_index\":2},{\"id\":5,\"port_index\":5},{\"id\":4,\"port_index\":6},{\"id\":6,\"port_index\":8}],\"alarms\":[{\"port_index\":1,\"alarm_value\":5.0,\"condition_type\":\"greater_than\"},{\"port_index\":1,\"alarm_value\":3.0,\"condition_type\":\"not_equal\"},{\"port_index\":1,\"alarm_value\":80.0,\"condition_type\":\"greater_than\"}]}\n";
    Sensor pSensors[MAX_NUMBER_OF_SENSORS];
    size_t iSensorsLength = 0;
    bool result;
    AlarmList* root;
    
    for(i = 0; i < MAX_NUMBER_OF_SENSORS ; i++)
        sensor_init(&pSensors[i], MOCK);    
    
    result = json_parse_sensors(json_buffer, pSensors, &iSensorsLength, MAX_NUMBER_OF_SENSORS);
    assert(result);
    assert(iSensorsLength == 5);
    root = pSensors[0].alarms;
    
    for(i = 0 ; i < 3 ; i++ ) {
        assert(root->next != NULL);
        root = root->next;
        assert(root->node->alarm_value == values[i]);
        assert(root->node->type == types[i]);
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% check_json_parse\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  test_json_parse_sensors (check_json_parse)\n");
    test_json_parse_sensors();
    printf("%%TEST_FINISHED%% time=0 test_json_parse_sensors (check_json_parse)\n");

    printf("%%TEST_STARTED%%  test_json_parse_alarms (check_json_parse)\n");
        test_json_parse_alarms();
    printf("%%TEST_FINISHED%% time=0 test_json_parse_alarms (check_json_parse)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
