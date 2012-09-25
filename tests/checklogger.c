/*
 * File:   checklogger.c
 * Author: supox
 *
 * Created on Sep 25, 2012, 2:17:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "logger.h"

/*
 * Simple C Test Suite
 */

void test1() {
    printf("checklogger test 1\n");
    add_to_log("Test log", NORMAL);
    add_to_log("Test Error", ERROR);
    add_to_log("Test Warning", WARNING);
    add_to_log("Test Dump", DUMP);
    
    logger_set_dump_mode(false);
    assert(logger_get_dump_mode() == false);
    add_to_log("THIS SHOULD NOT BE SEEN!", DUMP);
    logger_set_dump_mode(true);
    assert(logger_get_dump_mode() == true);
    add_to_log("THIS SHOULD BE SEEN!", DUMP);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% checklogger\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (checklogger)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (checklogger) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
