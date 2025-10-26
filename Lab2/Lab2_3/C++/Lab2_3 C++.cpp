#include <iostream>

using namespace std;

int readAndVerify(const int MIN_NUMBER, const int MAX_NUMBER, string str) 
{
    
    bool isIncorrect;
    int num;
    
    num = 0;
    isIncorrect = true;

    do
    {
        cout << str;
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
        }

    } while (isIncorrect);
    
    return num;
}

int **writeInMatrix(int n)
{
    const int MIN_NUMBER = -100000;
    const int MAX_NUMBER = 100000;

    int i;
    int j;
    int k;
    int **arrayA;

    i = 0;
    j = 0;
    k = 0;

    arrayA = new int *[n];
    for (k = 0; k < n; k++)
        arrayA[k] = new int[n];

    
    //cout << n << endl;
    //cout << sizeof(arrayA) << endl;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "Write element [" << i << "][" << j << "] of matrix: ";
            arrayA[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "Write element: ");
        }
    }

    return arrayA;
}

void writeOutMatrix(int **arrayA, int arrayLength)
{
    int i;
    int j;
    int n;

    i = 0;
    j = 0;
    //n = sizeof(arrayA) / sizeof(arrayA[0][0]);

    //cout << sizeof(arrayA) << endl;
    //cout << sizeof(arrayA[0][0]) << endl;
    //cout << n << endl;

    for (i = 0; i < arrayLength; i++)
    {
        for (j = 0; j < arrayLength; j++)
        {
            cout << arrayA[i][j] << " ";
        }
        cout << "\n";
    }
}

int **sortConditional(int **arrayA, int arrLength) // Попробовать не возвращать знавение а просто ссылкой менять массив
{

    int i;
    int j;
    int k;
    int limiter;
    int boubleSortLimiter;
    //int arrLength;

    i = 0;
    j = 0;
    k = 1;
    //arrLength = sizeof(arrayA) / sizeof(int);
    limiter = arrLength - 1;
    boubleSortLimiter = arrLength * (arrLength / 2);
    //arrLength = arrLength;

    for (k = 1; k < (boubleSortLimiter + 1); k++)
    {

        limiter = arrLength - 1;

        for (i = 0; i < arrLength; i++)
        {

            if (i % 2 == 1) 
            {
                if (i == (2 * (arrLength / 2)))
                    limiter = (arrLength - 1) - 1;

                for (j = 0; j < (limiter + 1); j++)
                {

                    if ((j + 1 < (arrLength - 1)) || (j + 1 == (arrLength - 1)))
                    {
                        if (arrayA[i][j] < arrayA[i][j + 1]) 
                        {
                            arrayA[i][j] = arrayA[i][j] + arrayA[i][j + 1];
                            arrayA[i][j + 1] = arrayA[i][j] - arrayA[i][j + 1];
                            arrayA[i][j] = arrayA[i][j] - arrayA[i][j + 1];
                        }
                    }
                    else if ((i + 2 < (arrLength - 1)) || (i + 2 == (arrLength - 1)))
                    {
                        if (arrayA[i][j] < arrayA[i + 2][0]) 
                        {
                            arrayA[i][j] = arrayA[i][j] + arrayA[i + 2][0];
                            arrayA[i + 2][0] = arrayA[i][j] - arrayA[i + 2][0];
                            arrayA[i][j] = arrayA[i][j] - arrayA[i + 2][0];
                        }   
                    }
                }
            }
        }
    }

    return arrayA;
}

int main()
{

    const int MIN_ORDER = 1;
    const int MAX_ORDER = 10;
    
    int n;
    int **a;
    int i;

    i = 0;

    n = readAndVerify(MIN_ORDER, MAX_ORDER, "Write the order of the matrix: ");

    a = writeInMatrix(n);

    //cout << sizeof(a) << endl;

    a = sortConditional(a, n);

    writeOutMatrix(a, n);

    for (i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}