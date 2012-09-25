/* 
 * File:   communication.h
 * Author: supox
 *
 * Created on September 25, 2012, 1:42 PM
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int state;
} CommunicationDescriptor;
    
bool comm_send_buffer(CommunicationDescriptor* comm, const char* buffer);
bool comm_send_byte(CommunicationDescriptor* comm, const char byte);
bool comm_recieve_buffer(CommunicationDescriptor* comm, char* buffer, size_t max_length);
bool comm_recieve_byte(CommunicationDescriptor* comm, char* byte);

CommunicationDescriptor* comm_create();
void comm_delete(CommunicationDescriptor* comm);

#endif	/* COMMUNICATION_H */

