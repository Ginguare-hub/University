#ifndef DS_H
#define DS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Queue
{
    int data[MAX];
    int front;    // Первый
    int rear;     // Последний
} Queue;

void initQueue(Queue *q);
_Bool checkIsEmpty(const Queue *q);
_Bool checkIsFull(const Queue *q);
_Bool enqueue(Queue *q, int value);
_Bool dequeue(Queue *q, int *value);
void printQueue(const Queue *q);
int queueSize(const Queue *q);

#endif