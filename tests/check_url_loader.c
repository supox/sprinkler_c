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

void test_post_web_page() {
    const char url[] = "http://localhost:3000/sprinklers/1/sensors/1/create_reading";
    const char req[] = "{\"sensor_reading\":{\"sensor_value\":10,\"read_time\":1349015174}}";
    StringBuffer* request = string_buffer_create();
    StringBuffer* response = string_buffer_create();
    string_buffer_write(request, req, strlen(req));
    
    bool result = post_web_page(url, request, response);
    assert(result);
    
    string_buffer_delete(request);
    string_buffer_delete(response);
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% check_url_loader\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testGet_web_page (check_url_loader)\n");
    testGet_web_page();
    printf("%%TEST_FINISHED%% time=0 testGet_web_page (check_url_loader)\n");
    
    printf("%%TEST_STARTED%%  test_post_web_page (check_url_loader)\n");
    test_post_web_page();
    printf("%%TEST_FINISHED%% time=0 test_post_web_page (check_url_loader)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
