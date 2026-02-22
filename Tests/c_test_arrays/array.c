#include "stdio.h"
#include "locale.h"
#include "malloc.h"

 int main(void) 
{
    int i;
    int element;
    int *array;
    int arrayLength;

    i = 0;

    setlocale(LC_ALL, "Russian");
    scanf("%d", &arrayLength);
    array = (int*)malloc(arrayLength * sizeof(int));

    for (i = 0; i < arrayLength; i++)
    {
        printf("¬ведите число номер %d: ", i);
        scanf("%d", &array[i]);
    }

    for (i = 0; i < arrayLength; i++)
    {
        printf("%d ", array[i]);
    }
    free(array);
    return 0;
}