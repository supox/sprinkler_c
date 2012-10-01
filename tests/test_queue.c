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

void test_sensor() {
    const int MaxElements = 10;
    MessageDescriptor message1, message2;
    
    // Init some data.
    message1.event_time=1;
    message1.id=2;
    message1.type=SENSOR_READING;
    message1.value=5;
    
    Queue q = queue_create(MaxElements);
    assert(q);
    
    assert(IsEmpty(q));
    assert(!IsFull(q));
    
    // check enqueue
    Enqueue(q, message1);
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
    Enqueue(q, message1);
    MakeEmpty(q);
    assert(IsEmpty(q));
    assert(!IsFull(q));
    
    queue_delete(q);
}

void test2() {
    const int MaxElements = 10;
    int iIndex;
    MessageDescriptor messages[MaxElements];
    Queue q = queue_create(MaxElements);

    assert(q);

    assert(IsEmpty(q));
    assert(!IsFull(q));

    for(iIndex = 0 ; iIndex < MaxElements ; iIndex++)
    {
        assert(!IsFull(q));
        
        messages[iIndex].event_time = iIndex;
        messages[iIndex].id = iIndex;
        messages[iIndex].type=SENSOR_READING;
        messages[iIndex].value=iIndex;
        
        // check enqueue
        Enqueue(q,messages[iIndex]);
    }
    
    assert(!IsEmpty(q));
    assert(IsFull(q));
    assert(Count(q)==MaxElements);


    for(iIndex = 0 ; iIndex < MaxElements ; iIndex++)
    {
        MessageDescriptor message = Dequeue(q);
        assert(AreEqual(&message,&messages[iIndex]));
    }
    
    assert(IsEmpty(q));
    assert(!IsFull(q));
    
    queue_delete(q);
    
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_queue\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (test_queue)\n");
    test_sensor();
    printf("%%TEST_FINISHED%% time=0 test1 (test_queue) \n");

    printf("%%TEST_STARTED%% test2 (test_queue)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (test_queue) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
