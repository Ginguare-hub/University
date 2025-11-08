#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int readAndVerify(const int MIN_NUMBER, const int MAX_NUMBER, string myString) 
{
    bool isIncorrect;
    int number;
    
    number = 0;
    isIncorrect = false;

    do
    {
      
        cout << myString;
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

bool isFileText(string filePath)
{
    const int MIN_PATH_LENGTH = 4;

    string fileExt;
    bool isText;
    //int strIndex;

    //strIndex = filePath.length();
    isText = true;

    if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.find(".txt") == string::npos))
        isText = false;

    return isText;
}

int main() 
{
    cout << isFileText("faf.txt");

    return 0;
}