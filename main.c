/* 
 * File:   main.c
 * Author: supox
 *
 * Created on September 24, 2012, 11:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "sprinkler.h"
#include "json_formatter.h"
#include "communication.h"

Sprinkler sprinkler;
CommunicationDescriptor comm;

void init();
bool read_sensors();
bool report_reading();
bool sleep_some_time();

/*
 * 
 */
int main(int argc, char** argv) {
    int i;
    init();

    for (i = 0; i < 5; i++) {
        if (read_sensors()) {
            report_reading();
        }

        sleep_some_time();
    }
    return (EXIT_SUCCESS);
}

void init() {
    /* initialize random seed: */
    srand(time(NULL));
    comm_init(&comm);

    sprinkler_initialize(&sprinkler);
}

bool read_sensors() {
    bool ret = sprinkler_read_sensors(&sprinkler);
    return ret;
}

bool report_reading() {
    // Build json string
    char message[256];
    if (!json_format_sensors(message, 256, sprinkler.sensors, sprinkler.number_of_sensors))
        return false;

    // Send message to server
    comm_send_buffer(&comm, message);

    return true;
}

bool sleep_some_time() {
    sleep(1);
}
