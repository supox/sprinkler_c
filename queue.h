/*
 *  FILE   : queue.h
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Define queue record structure and
 *           all forward declarations.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "message_descriptor.h"

typedef MessageDescriptor ElementType;

struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
int Count(Queue Q);
Queue queue_create(int MaxElements);
void queue_delete(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(Queue Q, ElementType X);
ElementType Front(Queue Q);
ElementType Dequeue(Queue Q);

#endif  /* _Queue_h */
