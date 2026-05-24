#include "ds.h"
#include "processing.h"

void fillQueueFromInput(Queue *q);
void writeOriginal();
void writeReversed();
void writePurpose();

int main(void) {
    Queue q;

    initQueue(&q);

    writePurpose();

    fillQueueFromInput(&q);
    writeOriginal();
    printQueue(&q);

    reverseQueue(&q);
    writeReversed();
    printQueue(&q);

    return 0;
}  

void fillQueueFromInput(Queue *q)
{
    const int MIN_LEN =     1;
    const int MAX_LEN =   101;
    const int MIN_NUM = -1000;
    const int MAX_NUM =  1000;

    int len, i, val;
    _Bool isNotFull;

    len = 0;
    isNotFull = 1;
    val = 0;

    printf("Enter length of queue [%d;%d]: \n", MIN_LEN, MAX_LEN);
    len = scanInt(MIN_LEN, MAX_LEN, "> ");
    printf("\nEnter elements in range [%d;%d]:\n", MIN_NUM, MAX_NUM);

    for (i = 0; i < len && isNotFull; ++i)
    {
        if (!checkIsFull(q))
        {
            printf("[%d]: ", i + 1);
            val = scanInt(MIN_NUM, MAX_NUM, "");
            enqueue(q, val);
        }
        else
        {
            printf("The queue is full\n");
            isNotFull = 0;
        }
    }
    printf("\n");
}

void writeOriginal()
{
    printf("\n=== ORIGINAL QUEUE ===\n");
}

void writeReversed()
{
    printf("\n=== REVERSED QUEUE ===\n"); 
}  

void writePurpose()
{
    printf("\n=== LAB 8: QUEUE REVERSAL (VARIANT 20) ===\n");
    printf(" - This program reverses a queue of integers\n");
    printf(" - Input: queue size and its elements\n");
    printf(" - Output: original queue and reversed queue\n");
    printf(" - Implementation uses a temporary array\n");
    printf("\n");
}