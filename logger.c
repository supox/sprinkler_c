#include "logger.h"
#include "config.h"
#include "time_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static FILE* logger_handle=NULL;
static bool logger_dump_mode = (bool)LOGGER_DUMP_MODE_DEFAULT;

static bool init_logger_handle() {
    logger_handle = fopen(LOGGER_FILENAME, "a");
    return (logger_handle != NULL);
}

static void logger_level_to_str(char str[], enum logger_level level, const size_t max_string_size){
    switch(level) {
    case DUMP:
        strncpy(str, "DUMP", max_string_size);
        break;
    case NORMAL: default:
        strncpy(str, "NORMAL", max_string_size);
        break;
    case WARNING:
        strncpy(str, "WARNING", max_string_size);
        break;
    case ERROR:
        strncpy(str, "ERROR", max_string_size);
        break;
    }
}

void add_to_log(const char* message, enum logger_level level) {
    time_t t;
    char logger_level_str[10]="";
    
    if(level == DUMP && !logger_dump_mode)
        return;
    
    if(logger_handle==NULL)
        if(!init_logger_handle())
            return;
    logger_level_to_str(logger_level_str, level, 10);
    
    t = get_time();
    fprintf(logger_handle, "%u %s : %s\n", (unsigned)t, logger_level_str, message);
    
    if(logger_dump_mode) // Log to console :
        printf("%u %s : %s\n", (unsigned)t, logger_level_str, message);
}

void logger_set_dump_mode(bool dump_mode) {
    logger_dump_mode = dump_mode;
}

bool logger_get_dump_mode() {
    return logger_dump_mode;
}