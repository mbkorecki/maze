#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

typedef struct Queue
{
	Cell *array;
	int back;
	int front;
	int size;
} Queue;

void doubleQueueSize(Queue *qp);
Queue newQueue(int s);
int isEmptyQueue(Queue q);
void queueEmptyError();
void enqueue(Cell item, Queue *qp);
Cell dequeue(Queue *qp);
void freeQueue(Queue q);

#endif
