/* 
 * File:   message_type.h
 * Author: supox
 *
 * Created on September 24, 2012, 11:35 PM
 */

#ifndef MESSAGE_TYPE_H
#define	MESSAGE_TYPE_H

enum message_type {
    LOG,
    SENSOR_READING,
    GENERAL_MESSAGE
};

void message_type_to_string(enum message_type message, char str[]);

#endif	/* MESSAGE_TYPE_H */

