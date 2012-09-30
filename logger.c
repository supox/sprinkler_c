#include "logger.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"

static FILE* logger_handle=NULL;
static bool logger_dump_mode = (bool)LOGGER_DUMP_MODE_DEFAULT;

static bool init_logger_handle() {
    logger_handle = fopen(LOGGER_FILENAME, "a");
    return (logger_handle != NULL);
}

static void logger_level_to_str(char str[], enum logger_level level){
    switch(level) {
    case DUMP:
        strcpy(str, "DUMP");
        break;
    case NORMAL: default:
        strcpy(str, "NORMAL");
        break;
    case WARNING:
        strcpy(str, "WARNING");
        break;
    case ERROR:
        strcpy(str, "ERROR");
        break;
    }
}

void add_to_log(char* message, enum logger_level level) {
    time_t t;
    char logger_level_str[10]="";
    
    if(level == DUMP && !logger_dump_mode)
        return;
    
    if(logger_handle==NULL)
        if(!init_logger_handle())
            return;
    logger_level_to_str(logger_level_str, level);
    
    t= time(NULL);
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