/*
 * File:   check_url_loader.c
 * Author: supox
 *
 * Created on Sep 29, 2012, 4:20:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "url_loader.h"
#include "config.h"

/*
 * Simple C Test Suite
 */

void testGet_web_page() {
    char url[] = SENSORS_CONFIGURATION_URL;
    StringBuffer* response = string_buffer_create();
    bool result = get_web_page(url, response);
    assert(result);
    string_buffer_delete(response);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% check_url_loader\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testGet_web_page (check_url_loader)\n");
    testGet_web_page();
    printf("%%TEST_FINISHED%% time=0 testGet_web_page (check_url_loader)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
