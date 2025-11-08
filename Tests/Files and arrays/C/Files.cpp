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

    isText = true;

    if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.find(".txt") == string::npos))
        isText = false;

    return isText;
}

bool isFileNotEmpty(fstream &inputFile)
{
    bool isFileNotEmpty;

    isFileNotEmpty = true;

    if (inputFile.eof())
        isFileNotEmpty = false;

    return isFileNotEmpty;
}

bool canRead(fstream &inputFile)
{
    bool isReady;

    isReady = inputFile.is_open();
    inputFile.close();

    return isReady;
}

// CanWrite

// CheckMyFile

bool workWithConsoleOrFile(bool isOutput)
{
    int number;
    bool isFromFile;

    number = 0;

    if (isOutput)
        cout << "If data is output to the console write 0, if from file write 1." << endl;
    else
        cout << "If data is entered from the console write 0, if from file write 1." << endl;

    number = readAndVerify(0, 1, "> ");

    if (number == 0)
    {
        isFromFile = false;
        if (isOutput)
            cout << "The data is output to the console." << endl;
        else
            cout << "The data is entered from the console." << endl;
    }
    else
    {
        isFromFile = true;
        if (isOutput)
            cout << "The data is output to a file." << endl;
        else
            cout << "The data is entered from a file." << endl;
    }

    return isFromFile;
}

string askTheFilePath()
{
    string filePath;

    cout << "Write the existing file path: ";

    cin >> filePath;

    // if (cin.fail() || cin.get() != '\n')
    // {
    //     cin.clear();
    //     while (cin.get() != '\n');
    // }

    return filePath;
}

void assignMyFile(ifstream& InputFile, bool isFileOutput)
{
    int number;
    bool isIncorrect; 
    string filePath;

    isIncorrect = false;

    do
    {
        isIncorrect = true;
        
        filePath = askTheFilePath();
        ifstream inputFile(filePath, ios::in/* | ios::out*/);

        cout << inputFile.fail();

        if (inputFile.fail())
        {
            isIncorrect = true;
            cout << "Error with assigning, try again." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        else
            isIncorrect = false;

        //IsCorrect := CheckMyFile(InputFile, FilePath, IsFileOutput);

    } while (isIncorrect);
    
}

// void checkAppendToFile(bool& isIncorrect, std::ofstream& inputFile)
// {
//     if (inputFile.fail())
// 	    {
// 	        isIncorrect = true;
// 	        std::cout << "" << std::endl;
// 	        inputFile.close();
// 	    }
// }

int main()
{
    // cout << isFileText("faf.txt");

    ifstream myFile;
    bool isOutput, isFromFile, isAllUndone;

    isOutput = true;

    isFromFile = workWithConsoleOrFile(isOutput);

    if (isFromFile) 
    {
        do
        {
            isAllUndone = false;

            assignMyFile(myFile, isOutput);

        } while (isFromFile);
        
    }





    isOutput = false;

    isFromFile = workWithConsoleOrFile(isOutput);

    return 0;
}