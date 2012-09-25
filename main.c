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

void init();
bool read_sensors();
bool report_reading();
bool sleep_some_time();

/*
 * 
 */
int main(int argc, char** argv) {
    init();
    
    read_sensors();
    report_reading();
    sleep_some_time();
    
    return (EXIT_SUCCESS);
}

void init() {
    /* initialize random seed: */
    srand ( time(NULL) );
}

bool read_sensors(){
    return false;
}
bool report_reading(){
    return false;
}
bool sleep_some_time() {
    return false;
}
