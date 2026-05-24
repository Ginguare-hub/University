#ifndef DS_H
#define DS_H

#define MAX_QUEUE_SIZE 100

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void init_queue(Queue *q);
int is_empty(const Queue *q);
int is_full(const Queue *q);
int enqueue(Queue *q, int value);
int dequeue(Queue *q, int *value);

#endif
