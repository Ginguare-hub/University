#include <stdio.h>
#include "formula.h"
#include "locale.h"

double scanX()
{
    int x;
    x = 0;
    printf("Введите величину потребления X: ");
    scanf("%d", &x);
    return x;
}

void printAnswer(int x)
{
    double s;
    s = 0;

    if (x >= 0)
    {
        s = calculate(x);
        printf("Тариф: %0.2f", s);
    }
    else
        printf("Число не может быть меньше чем 0.");
}

int main(void)
{
    int x;
    x = 0;

    setlocale(LC_ALL, "Russian");

    x = scanX();
    printAnswer(x);

    return 0;
}