#include <iostream>

using namespace std;

bool discoverIsNumberPrime(int number) 
{
    int i = 2;
    bool isShouldStop = false;
    bool isNumberPrime = false;

    for (i = 2; i < number; i++) 
    {
        if  ((number % i == 0) && (!isShouldStop))
        {
            isNumberPrime = false;
            isShouldStop = true;
        } 
        else if (!isShouldStop) 
            isNumberPrime = true;
    }

    if (number == 2) 
        isNumberPrime = true;

    return isNumberPrime;
}



int main()
{
    
    cout << discoverIsNumberPrime(3);
    
    
    return 0;
}
