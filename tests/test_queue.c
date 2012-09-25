/*
 * File:   test_queue.c
 * Author: supox
 *
 * Created on Sep 25, 2012, 2:30:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"
#include <stdbool.h>
/*
 * Simple C Test Suite
 */

bool AreEqual(MessageDescriptor *m1, MessageDescriptor *m2) {
    return (
            m1->event_time == m2->event_time &&
            m1->id == m2->id &&
            m1->type == m2->type &&
            m1->value == m2->value
    );
}

void test1() {
    const int MaxElements = 10;
    MessageDescriptor message1, message2;
    
    // Init some data.
    message1.event_time=1;
    message1.id=2;
    message1.type=SENSOR_READING;
    message1.value=5;
    
    Queue q = CreateQueue(MaxElements);
    assert(q);
    
    assert(IsEmpty(q));
    assert(!IsFull(q));
    
    // check enqueue
    Enqueue(message1,q);
    assert(!IsEmpty(q));
    assert(!IsFull(q));
    
    // check front
    message2 = Front(q);
    assert(AreEqual(&message1,&message2));
    assert(!IsEmpty(q));
    assert(!IsFull(q));

    // check dequeue
    message2 = Dequeue(q);
    assert(AreEqual(&message1,&message2));
    assert(IsEmpty(q));
    assert(!IsFull(q));
  
    // check make empty
    Enqueue(message1,q);
    MakeEmpty(q);
    assert(IsEmpty(q));
    assert(!IsFull(q));
    
    DisposeQueue(q);
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_queue\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test_queue)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (test_queue) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
