/*
 * File:   test_vector.c
 * Author: supox
 *
 * Created on Oct 13, 2012, 4:25:26 PM
 */

#include "token_vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Simple C Test Suite
 */

void test1() {
    TokenVector *v = token_vector_new();
    jsmntok_t t1, t2;
    size_t i;
    assert(v);
    
    t1.start = 1;
    t2.start = 2;
    
    assert(token_vector_add(v, &t1));
    assert(token_vector_add(v, &t2));
    assert(token_vector_get(v,0).start == t1.start);
    assert(token_vector_get(v,1).start == t2.start);
    assert(token_vector_size(v)==2);
    
    for(i=0;i<100;i++)
        assert(token_vector_add(v, &t2));
    assert(token_vector_size(v)==102);
    for(i=2;i<102;i++)
        assert(token_vector_get(v,i).start == t2.start);
    
    token_vector_destroy(v);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_vector\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test_vector)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (test_vector) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
