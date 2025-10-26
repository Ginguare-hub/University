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

int readAndVerify(const int MIN_NUMBER, const int MAX_NUMBER) 
{
    const int LOWEST_MERS = 3;
    
    bool isIncorrect;
    int num;
    
    num = 0;
    isIncorrect = true;

    do
    {
      
        cout << "Enter the number N: ";
        isIncorrect = false;

        cin >> num;

        if (cin.fail() || cin.get() != '\n')
        {
            isIncorrect = true;
            cout << "Incorrect input, try again." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }

        if (!isIncorrect && ((num < MIN_NUMBER) || (num > MAX_NUMBER)))
        {
            isIncorrect = true;
            cout << "The number must fit the range [" << MIN_NUMBER << "," << MAX_NUMBER << "]." << endl;
            if (num < (LOWEST_MERS + 1)) 
                cout << "There are no prime Mersenne numbers, lower then 3." << endl;
        }

    } while (isIncorrect);
    
    return num;
}

int getPrimeNumber(int inputNum)
{
    int number;
    int counter;
    int primeNumber;
    bool isMustStop;

    number = 2;
    counter = 0;
    primeNumber = 2;
    isMustStop = false;

    if (inputNum == 2)
        primeNumber = 3;
    else 
    {
        while (!isMustStop) 
        {
            if (discoverIsNumberPrime(number)) 
                counter++;

            if (counter == inputNum)
            {
                isMustStop = true;
                primeNumber = number;
            }
            
            number++;
        }
    }    
    return primeNumber;
}

void getMersenneNumbers(int n)
{
    const int MIN_ANSWER = 3;

    int i;
    int j;
    int answer;
    int mersenneNumber;

    i = 1;
    j = 2;
    answer = MIN_ANSWER;
    mersenneNumber = 2;

    while (answer < n)
    { 
        mersenneNumber = 2;
        
        for (j = 2; j < (getPrimeNumber(i) + 1); j++)
            mersenneNumber = mersenneNumber * 2;

        mersenneNumber = mersenneNumber - 1;
        answer = mersenneNumber;

        if ((discoverIsNumberPrime(answer) == true) && (answer < n))
        {
            if (i == 1)
                cout << "The answers is: " << endl;
            cout << answer << endl;
        }

        i++;
    }
}

int main()
{
    const int MIN_N = 4;
    const int MAX_N = 600000;
    
    int n;

    cout << "Programm is finding all numbers lower then N that is prime Mersenne numbers." << endl;

    n = readAndVerify(MIN_N, MAX_N);
    getMersenneNumbers(n);
    
    return 0;
}
