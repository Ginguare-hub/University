#include "ds.h"

void init_queue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int is_empty(const Queue *q) {
    int is_empty_status;

    if (q->front == q->rear) {
        is_empty_status = 1;
    } 
    else {
        is_empty_status = 0;
    }

    return is_empty_status;
}

int is_full(const Queue *q) {
    int is_full_status;

    if ((q->rear + 1) % MAX_QUEUE_SIZE == q->front) {
        is_full_status = 1;
    } 
    else {
        is_full_status = 0;
    }

    return is_full_status;
}

int enqueue(Queue *q, int value) {
    int success;

    if (is_full(q)) {
        success = 0;
    } 
    else {
        q->data[q->rear] = value;
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        success = 1;
    }

    return success;
}

int dequeue(Queue *q, int *value) {
    int success;

    if (is_empty(q)) {
        success = 0;
    } 
    else {
        *value = q->data[q->front];
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        success = 1;
    }

    return success;
}
