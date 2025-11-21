#include <iostream>

using namespace std;

int readAndVerify(const int MIN_NUMBER, const int MAX_NUMBER, string str)
{

    bool isIncorrect;
    int number;

    number = 0;
    isIncorrect = true;

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
            while (cin.get() != '\n')
                ;
        }

        if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
        {
            isIncorrect = true;
            cout << "The number must fit the range [" << MIN_NUMBER << "," << MAX_NUMBER << "]." << endl;
        }

    } while (isIncorrect);

    return number;
}

int *createArray()
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 30;
    const int MIN_NUMBER = -100000;
    const int MAX_NUMBER = 100000;

    int *myArray;
    int i, number, arrLength;
    bool isIncorrect;

    i = 0;
    number = 0;
    arrLength = 0;
    isIncorrect = false;

    arrLength = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write length of array: ");

    myArray = new int(arrLength);

    for (i = 0; i < arrLength; i++)
    {
        do
        {
            cout << "Element of array[" << i << "] = ";
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
}

void writeArray(int* myArray) 
{
    int i;

    i = 0;


}

int main()
{

    return 0;
}