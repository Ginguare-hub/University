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

bool isFileNotEmpty(ifstream &inputFile)
{
    bool isFileNotEmpty;

    isFileNotEmpty = true;

    if (inputFile.eof())
        isFileNotEmpty = false;

    return isFileNotEmpty;
}

bool canRead(ifstream &inputFile, string filePath)
{
    bool isReady;

    inputFile.open(filePath);

    if (inputFile.is_open())
    {
        inputFile.close();
        isReady = true;
    }
    else
        isReady = false;

    return isReady;
}

bool canWrite(ofstream &inputFile, string filePath)
{
    bool isReady;

    inputFile.open(filePath);

    if (inputFile.is_open())
    {
        inputFile.close();
        isReady = true;
    }
    else
        isReady = false;

    return isReady;
}

bool checkMyFile(ifstream &inputFile, string filePath)
{
    bool checkInput;

    checkInput = false;

    if (!(inputFile.good()))
        cout << "Error, file with path <" << filePath << "> is not exists." << endl;
    else 
        if (!isFileText(filePath))
            cout << "Error, filename is not .txt" << endl;
        else 
            if (!(canRead(inputFile, filePath)))
                cout << "Error, no access to read the file." << endl;
            else 
                if (!(isFileNotEmpty(inputFile)))
                    cout << "Error, file is empty." << endl;
                else
                {
                    checkInput = true;
                    cout << "Assigning is completed successfully." << endl;
                }

    return checkInput;
}

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

int readNumberFromFile(const int MIN_NUMBER, const int MAX_NUMBER, ifstream &inputFile, string filePath)
{
    const int ERROR_NUMBER = 37707;

    int number;
    bool isIncorrect;

    number = 0;
    isIncorrect = false;

    inputFile.open(filePath);
    inputFile >> number;

    if (cin.fail() || cin.get() != '\n')
    {
        isIncorrect = true;
        number = ERROR_NUMBER;
        cout << "Error, incorrect input." << endl;
    }

    if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
    {
        number = ERROR_NUMBER;
        cout << "The number must fit the range [" << MIN_NUMBER << "," << MAX_NUMBER << "]." << endl;
    }

    cout << "THE NUMBER IS " << number << endl; // GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG

    return number;
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

void assignMyFile(ifstream &inputFile, bool isFileOutput)
{
    int number;
    bool isIncorrect;
    string filePath;

    isIncorrect = false;

    do
    {
        isIncorrect = false;

        filePath = askTheFilePath();

        ifstream inputFile(filePath);

        if ((inputFile.rdstate() & ifstream::failbit) != 0)
        {
            //cout << "Error with assigning." << endl;
            isIncorrect = true;
        }

        isIncorrect = !(checkMyFile(inputFile, filePath));

        readNumberFromFile(1, 1000, inputFile, filePath);

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
    ifstream myFile;
    bool isOutput, isFromFile, isAllUndone;

    isOutput = false;

    isFromFile = workWithConsoleOrFile(isOutput);

    if (isFromFile)
    {
        do
        {
            isAllUndone = false;

            assignMyFile(myFile, isOutput);

        } while (isAllUndone);
    }

    isOutput = true;
    isFromFile = workWithConsoleOrFile(isOutput);

    return 0;
}