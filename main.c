/* 
 * File:   main.c
 * Author: supox
 *
 * Created on September 24, 2012, 11:32 PM
 */

#include "sprinkler.h"
#include "json_formatter.h"
#include "communication.h"
#include "time_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curl/curl.h>

Sprinkler sprinkler;
CommunicationDescriptor comm;

static void init();
static void destroy();
static bool do_sprinkler_tasks();
static bool sleep_some_time();

extern unsigned int sleep(unsigned int);
/*
 * 
 */
int main(int argc, char** argv) {
    int i;
    init();

    for (i = 0; i < 5; i++) {
        do_sprinkler_tasks();
        sleep_some_time();
    }

    destroy();
    return (EXIT_SUCCESS);
}

void init() {
    curl_global_init(CURL_GLOBAL_ALL);
    
    /* initialize random seed: */
    srand(get_time());
    comm_init(&comm);

    sprinkler_initialize(&sprinkler);
}

void destroy() {
    sprinkler_free_elements(&sprinkler);
    comm_free_elements(&comm);
    
    curl_global_cleanup();
}

bool do_sprinkler_tasks() {
    bool ret = true;
    if (sprinkler_needs_to_do_tasks(&sprinkler))
        ret = sprinkler_do_tasks(&sprinkler);
    return ret;
}

bool sleep_some_time() {
    unsigned int sleep_time_seconds;
    time_t next_reading_time = sprinkler_get_next_task_time(&sprinkler);
    time_t current_time = get_time();
    if(current_time >= next_reading_time)
        return true;
    else
        sleep_time_seconds = next_reading_time - current_time;
    
    sleep(sleep_time_seconds);
    return true;
}
