/* 
 * File:   logger.h
 * Author: supox
 *
 * Created on September 25, 2012, 12:52 AM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <stdbool.h>

enum logger_level {
    DUMP,
    NORMAL,
    WARNING,
    ERROR
};

void add_to_log(char* message, enum logger_level level);
void logger_set_dump_mode(bool dump_mode);
bool logger_get_dump_mode();

#endif	/* LOGGER_H */

