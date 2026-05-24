#include "processing.h"

void reverseQueue(Queue *q)
{
    int arr[MAX];
    int size, i;

    size = queueSize(q);

    // Извлекаем все элементы из очереди в массив
    for (i = 0; i < size; ++i) {
        dequeue(q, &arr[i]);
    }

    // Возвращаем элементы в обратном порядке
    for (i = size - 1; i >= 0; --i) {
        enqueue(q, arr[i]);
    }
}

int scanInt(const int MIN_NUMBER, const int MAX_NUMBER, const char myString[])
{
    _Bool isIncorrect;
    int number;
    char ch;

    isIncorrect = 0;
    number = 0;
    ch = 0;

    do
    {
        printf("%s", myString);
        isIncorrect = 0;

        if (scanf("%d%c", &number, &ch) == 0 || !(isspace(ch) || ch == EOF))
        {
            isIncorrect = 1;
            printf("Incorrect input, try again\n");
            while (getchar() != '\n')
                ;
        }

        if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
        {
            isIncorrect = 1;
            printf("Number must fit the [%d,%d] diapason\n", MIN_NUMBER, MAX_NUMBER);
        }

    } while (isIncorrect);

    return number;
}