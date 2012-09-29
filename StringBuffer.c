#include <stdlib.h>
#include <stdio.h>

#include "string_buffer.h"
#include "memory.h"
#include "logger.h"

void string_buffer_write(StringBuffer* sb, const char* s, const size_t size) {
    sb->memory = realloc(sb->memory, sb->size + size + 1);
    if (sb->memory == NULL) {
        /* out of memory! */
        add_to_log("not enough memory (realloc returned NULL)", ERROR);
    }

    memcpy(&(sb->memory[sb->size]), s, size);
    sb->size += size;
    sb->memory[sb->size] = 0;    
}

StringBuffer* string_buffer_create() {
    StringBuffer* sb = (StringBuffer*)malloc(sizeof(StringBuffer));
    if(sb)
        string_buffer_init(sb);
    return sb;
}

void string_buffer_init(StringBuffer* sb) {
    sb->memory = malloc(1);
    sb->size = 0;
}

void string_buffer_delete(StringBuffer* sb) {
    if(sb->memory)
        free(sb->memory);
    free(sb);
}

