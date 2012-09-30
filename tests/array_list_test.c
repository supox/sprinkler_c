/*
 * File:   alarm_list_test.c
 * Author: supox
 *
 * Created on Sep 30, 2012, 11:16:45 PM
 */

#include "alarm_list.h"
#include "alarm_type.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Simple C Test Suite
 */

void testAlarm_list_add() {
    AlarmList* root = alarm_list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    bool result;
    
    result = alarm_list_add(root, node1);
    assert(result);
    assert(root->next->node == node1);
    assert(root->next->next == NULL);

    result = alarm_list_add(root, node2);
    assert(result);
    assert(root->next->node == node1);
    assert(root->next->next->node == node2);
    assert(root->next->next->next == NULL);
    
    alarm_list_delete(root);
}

void testAlarm_list_create() {
    AlarmList* root = alarm_list_create();
    assert(root != NULL);
    assert(root->node == NULL);
    assert(root->next == NULL);
    alarm_list_delete(root);
}

void testAlarm_list_remove() {
    AlarmList* root = alarm_list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    Alarm* node3 = alarm_create(3, GREATER_THAN);
    bool result;
    
    alarm_list_add(root, node1);
    alarm_list_add(root, node2);
    alarm_list_add(root, node3);
    
    assert(root->next->node == node1);
    assert(root->next->next->node == node2);
    
    result = alarm_list_remove(root, node2);
    assert(result);
    assert(root->next->node == node1);
    assert(root->next->next->node == node3);
    assert(root->next->next->next == NULL);
    
    alarm_list_delete(root);
}

void testAlarm_list_will_alarm() {
    AlarmList* root = alarm_list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(5, GREATER_THAN);
    bool result;

    // No alarms
    result = alarm_list_will_alarm(root, 2);
    assert(!result);

    // One alarm, condition is not fulfills.
    alarm_list_add(root, node1);
    result = alarm_list_will_alarm(root, 2);
    assert(!result);
    
    // Two alarms, condition fulfills.
    alarm_list_add(root, node2);
    result = alarm_list_will_alarm(root, 2);
    assert(result);
    
    alarm_list_delete(root);
}

void testAlarm_list_contains() {
    AlarmList* root = alarm_list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    Alarm* node3 = alarm_create(3, GREATER_THAN);
    
    assert(!alarm_list_contains(root,node1));
    assert(!alarm_list_contains(root,node2));
    assert(!alarm_list_contains(root,node3));
    
    alarm_list_add(root, node1);
    assert(alarm_list_contains(root,node1));
    assert(!alarm_list_contains(root,node2));
    assert(!alarm_list_contains(root,node3));
    
    alarm_list_add(root, node2);
    assert(alarm_list_contains(root,node1));
    assert(alarm_list_contains(root,node2));
    assert(!alarm_list_contains(root,node3));

    alarm_list_add(root, node3);
    assert(alarm_list_contains(root,node1));
    assert(alarm_list_contains(root,node2));
    assert(alarm_list_contains(root,node3));
    
    alarm_list_remove(root, node2);
    assert(alarm_list_contains(root,node1));
    assert(!alarm_list_contains(root,node2));
    assert(alarm_list_contains(root,node3));
    
    alarm_list_delete(root);
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% alarm_list_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testAlarm_list_add (alarm_list_test)\n");
    testAlarm_list_add();
    printf("%%TEST_FINISHED%% time=0 testAlarm_list_add (alarm_list_test)\n");

    printf("%%TEST_STARTED%%  testAlarm_list_create (alarm_list_test)\n");
    testAlarm_list_create();
    printf("%%TEST_FINISHED%% time=0 testAlarm_list_create (alarm_list_test)\n");

    printf("%%TEST_STARTED%%  testAlarm_list_remove (alarm_list_test)\n");
    testAlarm_list_remove();
    printf("%%TEST_FINISHED%% time=0 testAlarm_list_remove (alarm_list_test)\n");

    printf("%%TEST_STARTED%%  testAlarm_list_will_alarm (alarm_list_test)\n");
    testAlarm_list_will_alarm();
    printf("%%TEST_FINISHED%% time=0 testAlarm_list_will_alarm (alarm_list_test)\n");

    printf("%%TEST_STARTED%%  testAlarm_list_contains (alarm_list_test)\n");
    testAlarm_list_contains();
    printf("%%TEST_FINISHED%% time=0 testAlarm_list_contains (alarm_list_test)\n");
    
    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
