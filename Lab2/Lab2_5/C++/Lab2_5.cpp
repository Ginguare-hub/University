#include <iostream>

using namespace std;

int readAndVerify(const int MIN_NUMBER, const int MAX_NUMBER, string str)
{

    bool isIncorrect;
    int number;

    isIncorrect = false;
    number = 0;

    do
    {
        cout << str << endl;
        cout << "> ";
        isIncorrect = false;

        cin >> number;

        if (cin.fail() || cin.get() != '\n')
        {
            isIncorrect = true;
            cout << "Incorrect input, try again." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }

        if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
        {
            isIncorrect = true;
            cout << "The number must fit the range [" << MIN_NUMBER << "," << MAX_NUMBER << "]." << endl;
        }

    } while (isIncorrect);

    return number;
}

int *createArray(int &arrLength)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 30;
    const int MIN_NUMBER = -100000;
    const int MAX_NUMBER = 100000;

    int *myArray;
    int i, number;
    bool isIncorrect;

    myArray = nullptr;
    i = 0;
    number = 0;
    isIncorrect = false;

    arrLength = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write length of array: ");

    myArray = new int(arrLength);

    for (i = 0; i < arrLength; i++)
    {
        do
        {
            cout << "Element of array[" << i << "] = ";
            cin >> number;
            isIncorrect = false;

            if (cin.fail() || cin.get() != '\n')
            {
                isIncorrect = true;
                cout << "Incorrect input, try again." << endl;
                cin.clear();
                while (cin.get() != '\n');
            }

            if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
            {
                isIncorrect = true;
                cout << "The number must fit the range [" << MIN_NUMBER << "," << MAX_NUMBER << "]." << endl;
            }

        } while (isIncorrect);

        myArray[i] = number;
    }

    return myArray;
}

void writeArray(int *myArray, int arrLength)
{
    int i;
    i = 0;
    for (i = 0; i < arrLength; i++)
        cout << myArray[i] << endl;
}

void changeArray(int *&myArray, int arrLength)
{
    const int LIMIT = 2;

    int i, j;

    i = 0;
    j = 0;

    for (i = 0; i < arrLength; i++)
        for (j = 0; j < arrLength; j++)
            if ((myArray[j] == 0) && !(myArray[i] == 0) && (i < j))
            {
                myArray[j] = myArray[j] + myArray[i];
                myArray[i] = myArray[j] - myArray[i];
                myArray[j] = myArray[j] - myArray[i];
            }

    for (i = 0; i < arrLength; i++)
        for (j = 0; j < arrLength; j++)
            if ((myArray[j] < 0) && !(myArray[i] == 0) && !(myArray[i] < 0) && (i < j))
            {
                myArray[j] = myArray[j] + myArray[i];
                myArray[i] = myArray[j] - myArray[i];
                myArray[j] = myArray[j] - myArray[i];
            }
}

int main()
{
    int arrLength;
    int *arrayA;

    arrLength = 0;
    arrayA = nullptr;
    
    arrayA = createArray(arrLength);
    changeArray(arrayA, arrLength);
    writeArray(arrayA, arrLength);

    delete[] arrayA;
    return 0;
}