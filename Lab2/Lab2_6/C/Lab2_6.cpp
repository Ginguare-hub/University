#include <iostream>

using namespace std;

int sumOfProperDivisors(int number) 
{
    int i, sumOfDivisors, numberDivTwo;

    i = 0;
    sumOfDivisors = 0;
    numberDivTwo = number / 2 + 1;

    for (i = 1; i < numberDivTwo; i++)
        if (number % i == 0)
            sumOfDivisors = sumOfDivisors + i;

    return sumOfDivisors;
} 

void findAnbicableNumbers()
{
    const int MY_LIMIT = 100001;

    int i, j, sumOfDivisors;

    i, sumOfDivisors = 0;
    j = 1;

    for (i = 1; i < MY_LIMIT; i++)
    {
        sumOfDivisors = sumOfProperDivisors(i);
        if ((i < sumOfDivisors) && (i == sumOfProperDivisors(sumOfDivisors)))
        {
            cout << j << ".  " << i << " And " << sumOfDivisors << endl;
            j++; 
        }
    }

}

int main() 
{
    findAnbicableNumbers();
    return 0;
}