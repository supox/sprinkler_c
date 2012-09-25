#include "communication.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

// This implementation is just read and write to the cout.

bool comm_send_buffer(CommunicationDescriptor* comm, const char* buffer) {
    time_t t = time(0);
    printf("%u : %s\n", (unsigned) t, buffer);
    return true;
}

bool comm_send_byte(CommunicationDescriptor* comm, const char byte) {
    time_t t = time(0);
    printf("%u : %c\n", (unsigned) t, byte);
    return true;
}

bool comm_recieve_buffer(CommunicationDescriptor* comm, char* buffer, size_t max_length) {
    int bytes_read = getline (&buffer, &max_length, stdin);
    return bytes_read > 0;
}

bool comm_recieve_byte(CommunicationDescriptor* comm, char* byte) {
    *byte = getchar();
    return (*byte != EOF);
}

CommunicationDescriptor* comm_create() {
    CommunicationDescriptor* comm;
    comm = (CommunicationDescriptor*) malloc (sizeof(CommunicationDescriptor));
    return comm;
}

void comm_delete(CommunicationDescriptor* comm) {
    free(comm);
}

