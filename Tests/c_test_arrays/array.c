#include "stdio.h"
#include "locale.h"
#include "malloc.h"

 int main(void) 
{
    int i, j;
    int element;
    int **array;
    int arrayLength;

    i = 0;

    setlocale(LC_ALL, "Russian");
    scanf("%d", &arrayLength);

    array = (int**)malloc(arrayLength * sizeof(int*));

    for (i = 0; i < arrayLength; i++)
    {
        array[i] = (int*)malloc(arrayLength * sizeof(int));

        for (j = 0; j < arrayLength; j++)
        {
            printf("¬ведите число номер %d,%d: ", i, j);
            scanf("%d", &array[i][j]);
        }
    }

    for (i = 0; i < arrayLength; i++)
    {
        for (j = 0; j < arrayLength; j++)
        {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }


    for (i = 0; i < arrayLength; i++)
    {
        free(array[i]);
    }
    free(array);

    return 0;
}