/* 
 * File:   StringBuffer.h
 * Author: supox
 *
 * Created on September 29, 2012, 1:39 PM
 */

#ifndef STRINGBUFFER_H
#define	STRINGBUFFER_H

#include <stdlib.h>

typedef struct {
    char *memory;
    size_t size;
    size_t pos;
} StringBuffer;

size_t string_buffer_write(StringBuffer* sb, const char* s, const size_t size);
size_t string_buffer_read(StringBuffer* sb, char* s, const size_t size);

StringBuffer* string_buffer_create();
void string_buffer_init(StringBuffer* sb);
void string_buffer_delete(StringBuffer* sb);

#endif	/* STRINGBUFFER_H */

