#include "ds.h"

// Операции:
// • enqueue      // Вставить в очередь
// • dequeue      // Вытянуть из очереди
// • is_empty     // Проверка на пустоту

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
}

_Bool checkIsEmpty(const Queue *q)
{
    _Bool isEmpty;
    isEmpty = 0;

    if (q->front == q->rear)
        isEmpty = 1;

    return isEmpty;
}

_Bool checkIsFull(const Queue *q)
{
    int isFull;
    isFull = 0;

    if ((q->rear + 1) % MAX == q->front)
        isFull = 1;

    return isFull;
}

_Bool enqueue(Queue *q, int value)
{
    _Bool isSuccess;

    if (checkIsFull(q))
        isSuccess = 0;
    else
    {
        q->data[q->rear] = value;
        q->rear = (q->rear + 1) % MAX;
        isSuccess = 1;
    }

    return isSuccess;
}

_Bool dequeue(Queue *q, int *value)
{
    _Bool isSuccess;

    if (checkIsEmpty(q))
        isSuccess = 0;
    else
    {
        *value = q->data[q->front];
        q->front = (q->front + 1) % MAX;
        isSuccess = 1;
    }

    return isSuccess;
}
