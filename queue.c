/*
 *  FILE   : queue.c
 *  AUTHOR : Jeffrey Hunter
 *  WEB    : http://www.iDevelopment.info
 *  NOTES  : Implement all functions required
 *           for a Queue data structure.
 */

#include "queue.h"
#include <stdlib.h>

#define Error(Str)        FatalError(Str)
#define FatalError(Str)   fprintf(stderr, "%s\n", Str), exit(1)

#define MinQueueSize (5)

struct QueueRecord {
  int Capacity;
  int Front;
  int Rear;
  int Size;
  ElementType *Array;
};

int IsEmpty(Queue Q) {
  return Q->Size == 0;
}

int IsFull(Queue Q) {
  return Q->Size == Q->Capacity;
}

int Count(Queue Q) {
    return Q->Size;
}
Queue queue_create(int MaxElements) {
  Queue Q;

  if (MaxElements < MinQueueSize) {
    Error("CreateQueue Error: Queue size is too small.");
  }

  Q = malloc (sizeof(struct QueueRecord));
  if (Q == NULL) {
    FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Array = malloc( sizeof(ElementType) * MaxElements );
  if (Q->Array == NULL) {
    FatalError("CreateQueue Error: Unable to allocate more memory.");
  }

  Q->Capacity = MaxElements;
  MakeEmpty(Q);

  return Q;
}

void MakeEmpty(Queue Q) {

  Q->Size = 0;
  Q->Front = 1;
  Q->Rear = 0;

}

void queue_delete(Queue Q) {
  if (Q != NULL) {
    free(Q->Array);
    free(Q);
  }
}

static int Succ(int Value, Queue Q) {
  if (++Value == Q->Capacity) {
    Value = 0;
  }
  return Value;
}

void Enqueue(Queue Q, ElementType X) {

  if (IsFull(Q)) {
    Error("Enqueue Error: The queue is full.");
  } else {
    Q->Size++;
    Q->Rear = Succ(Q->Rear, Q);
    Q->Array[Q->Rear] = X;
  }

}

ElementType Front(Queue Q) {

  if (!IsEmpty(Q)) {
    return Q->Array[Q->Front];
  }
  Error("Front Error: The queue is empty.");

  /* Return value to avoid warnings from the compiler */
  ElementType ret;
  return ret;

}

ElementType Dequeue(Queue Q) {

  ElementType X;

  if (IsEmpty(Q)) {
    Error("FrontAndDequeue Error: The queue is empty.");
  } else {
    Q->Size--;
    X = Q->Array[Q->Front];
    Q->Front = Succ(Q->Front, Q);
  }
  return X;

}
