/*
 * File:   string_buffer_test.c
 * Author: supox
 *
 * Created on Sep 29, 2012, 1:56:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "string_buffer.h"

/*
 * Simple C Test Suite
 */

void test_string_buffer() {
    StringBuffer* sb = string_buffer_create();
    
    char str1[]="LALALA";
    char str2[]="ASDASDA";
    
    assert(strcmp(sb->memory, "") == 0);
    string_buffer_write(sb, str1, strlen(str1));
    assert(strcmp(sb->memory, str1) == 0);

    string_buffer_write(sb, str2, strlen(str2));
    assert(strcmp(sb->memory, "LALALAASDASDA") == 0);

     
    string_buffer_delete(sb);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% string_buffer_test\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test_string_buffer (string_buffer_test)\n");
    test_string_buffer();
    printf("%%TEST_FINISHED%% time=0 test1 (string_buffer_test) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
