/* 
 * File:   message_descriptor.h
 * Author: supox
 *
 * Created on September 24, 2012, 11:34 PM
 */

#ifndef MESSAGE_DESCRIPTOR_H
#define	MESSAGE_DESCRIPTOR_H

#include "message_type.h"
#include <stdio.h>
#include <time.h>

typedef struct
{
    int id;
    enum message_type type;
    time_t event_time;
    int value;
} MessageDescriptor;

#endif	/* MESSAGE_DESCRIPTOR_H */
