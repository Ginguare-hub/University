#include <iostream>
#include <cmath>

using namespace std;

int main() 
{

    typedef double tArr;

    tArr* arr; 
    int length, i, answer;
    tArr num, minDiff, absDiff, sumOfNums, arithmMean;
    
    sumOfNums = 0;
    minDiff = 0;

    cin >> length;

    arr = new tArr[length];

    for (i = 0; i < length; i++) 
    {
        cout << "Element " << i + 1 << " = ";
        cin >> num;
        arr[i] = num;
        sumOfNums = sumOfNums + num;
    } 

    arithmMean = sumOfNums / length;
    minDiff = abs(arithmMean - arr[0]);
    absDiff = arr[0];

    for (i = 0; i < length; i++)
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
