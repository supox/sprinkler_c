#include "communication.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

// This implementation is just read and write to the cout.

bool comm_send_buffer(CommunicationDescriptor* comm, const char* buffer) {
    time_t t = time(NULL);
    printf("%u : %s\n", (unsigned) t, buffer);
    return true;
}

bool comm_send_byte(CommunicationDescriptor* comm, const char byte) {
    time_t t = time(NULL);
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
    CommunicationDescriptor* comm = (CommunicationDescriptor*) malloc (sizeof(CommunicationDescriptor));
    if(comm)
        comm_init(comm);
    return comm;
}

void comm_init(CommunicationDescriptor* comm) {
    comm->state = 0;
}

void comm_delete(CommunicationDescriptor* comm) {
    free(comm);
}

