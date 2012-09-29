/* 
 * File:   url_loader.h
 * Author: supox
 *
 * Created on September 29, 2012, 4:12 PM
 */

#ifndef URL_LOADER_H
#define	URL_LOADER_H

#include <stdbool.h>
#include "string_buffer.h"

bool get_web_page(const char* url, StringBuffer* response);

#endif	/* URL_LOADER_H */

