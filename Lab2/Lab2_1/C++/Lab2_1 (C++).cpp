#include <iostream>
#include <cmath>

using namespace std;

int main() 
{

    typedef double tArr;

    const int MAX_LENGTH = 20;
    const int MIN_LENGTH = 1;
    const tArr MAX_NUM = 12345.0;
    const tArr MIN_NUM = -12345.0;

    int arrLength, i, answer;
    bool isIncorrect;
    tArr num, minDiff, absDiff, sumOfNums, arithmMean;
    tArr* arr; 

    arrLength = 1;
    i = 0;
    answer = 1;
    num = 0;
    arithmMean = 0;
    minDiff = 0;
    absDiff = 0;
    sumOfNums = 0;
    isIncorrect = false;
    
    do
        {
            std::cout << "Enter the number of numbers in the list: ";
            std::cin >> arrLength;

            isIncorrect = false;

            if (std::cin.get() != '\n' || std::cin.fail())
            {
                isIncorrect = true;
                std::cout << "Incorrect input, try again." << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n');
            }

            if (!isIncorrect && ((arrLength < MIN_LENGTH) || (arrLength > MAX_LENGTH)))
            {
                isIncorrect = true;
                std::cout << "The number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << std::endl;
                while (std::cin.get() != '\n');
            }  

        } while (isIncorrect);

    arr = new tArr[arrLength];

    for (i = 0; i < arrLength; i++) 
    {
        do
        {
            std::cout << "Element " << i + 1 << " = ";
            std::cin >> num;

            isIncorrect = false;

            if (std::cin.get() != '\n' || std::cin.fail())
            {
                isIncorrect = true;
                std::cout << "Incorrect input, try again." << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n');
            }

            if (!isIncorrect && ((num < MIN_NUM) || (num > MAX_NUM)))
            {
                isIncorrect = true;
                std::cout << "The number must fit the range [" << MIN_NUM << "," << MAX_NUM << "]." << std::endl;
                while (std::cin.get() != '\n');
            }  

        } while (isIncorrect);
        
        arr[i] = num;
        sumOfNums = sumOfNums + num;
    } 

    arithmMean = sumOfNums / arrLength;
    minDiff = abs(arithmMean - arr[0]);
    absDiff = arr[0];

    for (i = 0; i < arrLength; i++)
    {
        absDiff = abs(arithmMean - arr[i]);

        if (minDiff > absDiff) 
        {
            minDiff = absDiff;
            answer = i + 1;
        }
    }

    cout << "The element " << answer << " in the list is the number, that most fits with the arithmetic mean of the series." << endl;

    delete[] arr;
    return 0;
}
