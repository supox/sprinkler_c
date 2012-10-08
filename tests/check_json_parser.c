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
#include "alarm.h"
#include "valf.h"

/*
 * Simple C Test Suite
 */

void test_json_parse_sensors() {
    const int ids[]={1,2,5,4,6};
    const int ports[]={1,2,5,6,8};
    const double alarms_values[]={5,3,80};
    const enum AlarmType alarms_types[] = {GREATER_THAN, NOT_EQUAL, GREATER_THAN};
    
    int i;
    const char* json_buffer = "{\"sensors\":[{\"id\":1,\"port_index\":1},{\"id\":2,\"port_index\":2},{\"id\":5,\"port_index\":5},{\"id\":4,\"port_index\":6},{\"id\":6,\"port_index\":8}],\"alarms\":[{\"port_index\":1,\"alarm_value\":5.0,\"condition_type\":\"greater_than\"},{\"port_index\":1,\"alarm_value\":3.0,\"condition_type\":\"not_equal\"},{\"port_index\":1,\"alarm_value\":80.0,\"condition_type\":\"greater_than\"}]}\n";
    ListElement* sensors = sensor_create_list();
    ListElement* root_sensors;
    ListElement* root_alarms;
    bool result;
        
    result = json_parse_sensors(json_buffer, sensors);
    assert(result);
    assert(list_count(sensors) == 5);
    
    for (i=0, root_sensors = sensors->next; root_sensors != NULL; root_sensors = root_sensors->next, ++i) {
        Sensor* sensor = (Sensor*)root_sensors->node;
        assert(sensor->port_index==ports[i]);
        assert(sensor->id==ids[i]);
    }
    
    root_alarms = ((Sensor*)(sensors->next->node))->alarms;
    assert(list_count(root_alarms)==3);
    
    for (i=0, root_alarms = root_alarms->next; root_alarms != NULL; root_alarms = root_alarms->next, ++i) {
        Alarm* alarm = (Alarm*)root_alarms->node;

        assert(alarm->alarm_value == alarms_values[i]);
        assert(alarm->type == alarms_types[i]);
    }
    
    list_delete(sensors);
}

void check_parse_valves() {
    const int ids[]={4,6,5};
    const int ports[]={1,2,4};
    
    const char valf_json[] = "[{\"id\":4,\"port_index\":1},{\"id\":6,\"port_index\":2},{\"id\":5,\"port_index\":4}]\n";
    ListElement* valves = valf_create_list();
    int i;
    bool result;
    ListElement* root_valves;
        
    result = json_parse_valves(valf_json, valves);
    assert(result);
    assert(list_count(valves) == 3);
    
    for (i=0, root_valves = valves->next; root_valves != NULL; root_valves = root_valves->next, ++i) {
        Valf* valf = (Valf*)root_valves->node;
        assert(valf->port_index==ports[i]);
        assert(valf->id==ids[i]);
    }    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% check_json_parse\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  test_json_parse_sensors (check_json_parse)\n");
    test_json_parse_sensors();
    printf("%%TEST_FINISHED%% time=0 test_json_parse_sensors (check_json_parse)\n");

    printf("%%TEST_STARTED%%  check_parse_valves (check_json_parse)\n");
    check_parse_valves();
    printf("%%TEST_FINISHED%% time=0 test_json_parse_sensors (check_json_parse)\n");
    
    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
