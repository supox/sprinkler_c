/*
 * File:   check_communication.c
 * Author: supox
 *
 * Created on Sep 25, 2012, 2:26:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "communication.h"

/*
 * Simple C Test Suite
 */

void test1() {
    CommunicationDescriptor* comm;
    printf("check_communication test 1\n");
    
    comm = comm_create();
    assert(comm_send_buffer(comm, "Communication Test"));
    assert(comm_send_byte(comm, 'b'));
        
    comm_delete(comm);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% check_communication\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (check_communication)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (check_communication) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
