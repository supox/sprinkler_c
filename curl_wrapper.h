/* 
 * File:   curl_wrapper.h
 * Author: supox
 *
 * Created on September 29, 2012, 1:24 PM
 */

#ifndef CURL_WRAPPER_H
#define	CURL_WRAPPER_H

typedef struct {
    char *memory;
    size_t size;
} StringBuffer;

bool load_json_data(const char* url, StringBuffer* buffer);

#endif	/* CURL_WRAPPER_H */

