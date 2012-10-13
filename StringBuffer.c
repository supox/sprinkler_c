#include <stdlib.h>
#include <stdio.h>

#include "string_buffer.h"
#include "memory.h"
#include "logger.h"

static bool string_buffer_reallocate_buffer(StringBuffer* sb, const size_t new_number_of_elements);

size_t string_buffer_write(StringBuffer* sb, const char* s, const size_t size) {
    if(!string_buffer_reallocate_buffer(sb, sb->write_pos + size + 1)) {
        /* out of memory! */
        add_to_log("not enough memory (realloc returned NULL)", ERROR);
        return 0;
    }

    memcpy(&(sb->memory[sb->write_pos]), s, size);
    sb->write_pos += size;
    sb->memory[sb->write_pos] = 0;

    return size;
}

size_t string_buffer_read(StringBuffer* sb, char* s, const size_t size) {
    const size_t bytes_left = sb->write_pos - sb->read_pos;
    size_t realsize = size;
    if (realsize > bytes_left)
        realsize = bytes_left;

    if (realsize > 0) {
        memcpy(s, &(sb->memory[sb->read_pos]), realsize);
        sb->read_pos += realsize;
    }

    return realsize;
}

StringBuffer* string_buffer_create() {
    StringBuffer* sb = (StringBuffer*) malloc(sizeof (StringBuffer));
    if (sb)
        string_buffer_init(sb);
    return sb;
}

void string_buffer_init(StringBuffer* sb) {
    sb->memory = malloc(1);
    sb->write_pos = 0;
    sb->read_pos = 0;
}

void string_buffer_delete(StringBuffer* sb) {
    if (sb->memory)
        free(sb->memory);
    free(sb);
}

bool string_buffer_reallocate_buffer(StringBuffer* sb, const size_t new_number_of_elements) {
    char* new_buf = realloc(sb->memory, sizeof(char) * new_number_of_elements);
    if(new_buf != NULL) {
        sb->memory = new_buf;
        return true;
    }
    return false;    
}
