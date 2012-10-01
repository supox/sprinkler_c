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

Sprinkler sprinkler;
CommunicationDescriptor comm;

static void init();
static bool read_sensors();
static bool report_readings();
static bool sleep_some_time();

extern unsigned int sleep(unsigned int);
/*
 * 
 */
int main(int argc, char** argv) {
    int i;
    init();

    for (i = 0; i < 120; i++) {
        if (read_sensors()) {
            report_readings();
        }
        sleep_some_time();
    }

    sprinkler_free_elements(&sprinkler);
    return (EXIT_SUCCESS);
}

void init() {
    /* initialize random seed: */
    srand(get_time());
    comm_init(&comm);

    sprinkler_initialize(&sprinkler);
}

bool read_sensors() {
    bool ret = sprinkler_read_sensors(&sprinkler);
    return ret;
}

bool report_readings() {
    bool ret = true;
    if (sprinkler_needs_to_report_reading(&sprinkler))
        ret = sprinkler_report_reading(&sprinkler);
    return ret;
}

bool sleep_some_time() {
    sleep(1);
    return true;
}
