#include <stdio.h>
#include "formula.h"

int main(void) 
{
    int x = 3;
    int result = calculate(x);

    printf("f(%d) = %d\n", x, result);
    
    return 0;
}