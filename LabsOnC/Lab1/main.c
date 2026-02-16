#include <stdio.h>
#include "formula.h"

int main(void) 
{
    int x;
    double s;
    _Bool isCorrect;

    x = 0;
    s = 0;
    isCorrect = 0;

    scanf("%d", &x);
    s = calculate(x);

    printf("%f", s);

    return 0;
}