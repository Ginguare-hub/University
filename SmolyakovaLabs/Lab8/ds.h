#ifndef DS
#define DS

#include <stdio.h>
#include <stdlib>

#define MAX = 100

typedef struct Queue
{
    int data[MAX];
    int front;    // Первый
    int rear;     // Последний
} Queue;

void init_queue(Queue *q);
int is_empty(const Queue *q);
int is_full(const Queue *q);
int enqueue(Queue *q, int value);
int dequeue(Queue *q, int *value);

#endif