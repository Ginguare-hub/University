#include <iostream>
#include <cmath>

using namespace std;

int main()
{

    const int MAX_LENGTH = 20;
    const int MIN_LENGTH = 1;
    const double MAX_NUM = 12345.0;
    const double MIN_NUM = -12345.0;

    int arrLength, i;
    bool isIncorrect;
    double num, minDiff, currDiff, sumOfNums, arithmMean;
    double *arr;

    arrLength = 1;
    i = 0;
    num = 0;
    arithmMean = 0;
    minDiff = 0;
    currDiff = 0;
    sumOfNums = 0;
    isIncorrect = false;

    cout << "Programm finds the element(s) in the list, that most fits with the arithmetic mean of the series." << endl;

    do
    {
        cout << "Enter the number of numbers in the list: ";
        cin >> arrLength;

        isIncorrect = false;

        if (cin.get() != '\n' || cin.fail())
        {
            isIncorrect = true;
            cout << "Incorrect input, try again." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }

        if (!isIncorrect && ((arrLength < MIN_LENGTH) || (arrLength > MAX_LENGTH)))
        {
            isIncorrect = true;
            cout << "The number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
        }

    } while (isIncorrect);

    arr = new double[arrLength];

    for (i = 0; i < arrLength; i++)
    {
        do
        {
            cout << "Element " << i + 1 << " = ";
            cin >> num;

            isIncorrect = false;

            if (cin.get() != '\n' || cin.fail())
            {
                isIncorrect = true;
                cout << "Incorrect input, try again." << endl;
                cin.clear();
                while (cin.get() != '\n');
            }

            if (!isIncorrect && ((num < MIN_NUM) || (num > MAX_NUM)))
            {
                isIncorrect = true;
                cout << "The number must fit the range [" << MIN_NUM << "," << MAX_NUM << "]." << endl;
                while (cin.get() != '\n');
            }

        } while (isIncorrect);

        arr[i] = num;
        sumOfNums = sumOfNums + num;
    }

    arithmMean = sumOfNums / arrLength;
    minDiff = abs(arithmMean - arr[0]);

    for (i = 0; i < arrLength; i++)
    {
        currDiff = abs(arithmMean - arr[i]);

        if (minDiff > currDiff)
        {
            minDiff = currDiff;
        }
    }

    cout << "The element(s) ";

    for (i = 0; i < arrLength; i++)
    {
        currDiff = abs(arithmMean - arr[i]);

        if (minDiff == currDiff)
            cout << i + 1 << " ";
    }

    cout << "in the list is the number(s), that most fits with the arithmetic mean of the series." << endl;

    delete[] arr;
    return 0;
}
