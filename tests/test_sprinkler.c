/*
 * File:   test_sprinkler.c
 * Author: supox
 *
 * Created on Sep 29, 2012, 10:19:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sprinkler.h"

/*
 * Simple C Test Suite
 */

void testSprinkler_init() {
    Sprinkler* s = sprinkler_create();
    assert(s != NULL);
    
    sprinkler_delete(s);

}

void test_sprinkler_do_tasks() {
    bool result;
    Sprinkler* s = sprinkler_create();
    assert(s != NULL);
    
    result = sprinkler_do_tasks(s);
    assert(result); // TODO - check result
    
    sprinkler_delete(s);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_sprinkler\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testSprinkler_load_config (test_sprinkler)\n");
    testSprinkler_init();
    printf("%%TEST_FINISHED%% time=0 testSprinkler_load_config (test_sprinkler)\n");

    printf("%%TEST_STARTED%%  testSprinkler_read_sensors (test_sprinkler)\n");
    test_sprinkler_do_tasks();
    printf("%%TEST_FINISHED%% time=0 testSprinkler_read_sensors (test_sprinkler)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
