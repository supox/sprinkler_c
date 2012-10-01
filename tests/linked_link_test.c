/*
 * File:   linked_list_test.c
 * Author: supox
 *
 * Created on Oct 1, 2012, 21:07:01 PM
 */

#include "linked_list.h"
#include "alarm.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Simple C Test Suite
 */

void test_list_add() {
    ListElement* root = list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    bool result;

    result = list_add(root, node1);
    assert(result);
    assert(root->next->node == node1);
    assert(root->next->next == NULL);

    result = list_add(root, node2);
    assert(result);
    assert(root->next->node == node1);
    assert(root->next->next->node == node2);
    assert(root->next->next->next == NULL);

    list_delete(root);
}

void test_list_create() {
    ListElement* root = list_create();
    assert(root != NULL);
    assert(root->node == NULL);
    assert(root->next == NULL);
    list_delete(root);
}

void test_list_remove() {
    ListElement* root = list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    Alarm* node3 = alarm_create(3, GREATER_THAN);
    bool result;

    list_add(root, node1);
    list_add(root, node2);
    list_add(root, node3);

    assert(root->next->node == node1);
    assert(root->next->next->node == node2);

    result = list_remove(root, node2);
    assert(result);
    assert(root->next->node == node1);
    assert(root->next->next->node == node3);
    assert(root->next->next->next == NULL);

    list_delete(root);
}

void test_list_contains() {
    ListElement* root = list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    Alarm* node3 = alarm_create(3, GREATER_THAN);

    assert(!list_contains(root, node1));
    assert(!list_contains(root, node2));
    assert(!list_contains(root, node3));
    assert(list_count(root) == 0);

    list_add(root, node1);
    assert(list_contains(root, node1));
    assert(!list_contains(root, node2));
    assert(!list_contains(root, node3));
    assert(list_count(root) == 1);

    list_add(root, node2);
    assert(list_contains(root, node1));
    assert(list_contains(root, node2));
    assert(!list_contains(root, node3));
    assert(list_count(root) == 2);

    list_add(root, node3);
    assert(list_contains(root, node1));
    assert(list_contains(root, node2));
    assert(list_contains(root, node3));
    assert(list_count(root) == 3);

    list_remove(root, node2);
    assert(list_contains(root, node1));
    assert(!list_contains(root, node2));
    assert(list_contains(root, node3));
    assert(list_count(root) == 2);

    list_delete(root);

}

void test_list_clear() {
    ListElement* root = list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    Alarm* node3 = alarm_create(3, GREATER_THAN);

    list_add(root, node1);
    list_add(root, node2);
    list_add(root, node3);
    assert(list_count(root) == 3);

    list_clear(root);
    assert(list_count(root) == 0);

    node1 = alarm_create(1, GREATER_THAN);
    list_add(root, node1);
    assert(list_count(root) == 1);

    list_clear(root);
    assert(list_count(root) == 0);

    list_delete(root);
}

void test_list_empty() {
    ListElement* root = list_create();
    Alarm* node1 = alarm_create(1, GREATER_THAN);
    Alarm* node2 = alarm_create(2, GREATER_THAN);
    Alarm* node3 = alarm_create(3, GREATER_THAN);

    assert(list_empty(root));
    list_add(root, node1);
    assert(!list_empty(root));
    list_add(root, node2);
    assert(!list_empty(root));
    list_add(root, node3);
    assert(!list_empty(root));
    
    list_remove(root,node1);
    assert(!list_empty(root));
    list_remove(root,node2);
    assert(!list_empty(root));
    list_remove(root,node3);
    assert(list_empty(root));
    
    node1 = alarm_create(1, GREATER_THAN);
    list_add(root, node1);
    assert(!list_empty(root));

    list_clear(root);
    assert(list_empty(root));

    list_delete(root);    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% list_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  test_list_add (list_test)\n");
    test_list_add();
    printf("%%TEST_FINISHED%% time=0 test_list_add (list_test)\n");

    printf("%%TEST_STARTED%%  test_list_create (list_test)\n");
    test_list_create();
    printf("%%TEST_FINISHED%% time=0 test_list_create (list_test)\n");

    printf("%%TEST_STARTED%%  test_list_remove (list_test)\n");
    test_list_remove();
    printf("%%TEST_FINISHED%% time=0 test_list_remove (list_test)\n");

    printf("%%TEST_STARTED%%  test_list_contains (list_test)\n");
    test_list_contains();
    printf("%%TEST_FINISHED%% time=0 test_list_contains (list_test)\n");

    printf("%%TEST_STARTED%%  test_list_clear (list_test)\n");
    test_list_clear();
    printf("%%TEST_FINISHED%% time=0 test_list_clear (list_test)\n");

    printf("%%TEST_STARTED%%  test_list_empty (list_test)\n");
    test_list_empty();
    printf("%%TEST_FINISHED%% time=0 test_list_empty (list_test)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
