#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writePurpose() 
{
    cout << "REWRITE_REWRITE_REWRITE" << endl;
}

int readAndVerify(const int MIN_NUMBER, const int MAX_NUMBER, string myString)
{
    bool isIncorrect;
    int number;

    isIncorrect = false;
    number = 0;

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

    fileExt = "";
    isText = true;

    if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.find(".txt") == string::npos))
        isText = false;

    return isText;
}

bool canRead(string filePath)
{
    bool isReady;
    ifstream testFile;

    isReady = false;
    testFile.open(filePath);

    if (testFile.is_open())
    {
        testFile.close();
        isReady = true;
    }

    testFile.close();
    return isReady;
}

bool canWrite(const string &filePath)
{
    ofstream outputFile;
    bool canWrite;
    
    canWrite = false;
    
    outputFile.open(filePath, ios::app);
    canWrite = outputFile.is_open();
    outputFile.close();

    outputFile.close();
    return canWrite;
}

bool checkMyFile(string filePath, bool isFileOutput)
{
    ifstream testFile;
    bool checkInput;
    
    checkInput = false;

    testFile.open(filePath);

    if (testFile.fail())
    {
        cout << "Error, file with path <" << filePath << "> is not exists or cannot be read." << endl;
        testFile.close();
    }
    else 
        if (!isFileText(filePath))
            cout << "Error, filename is not .txt" << endl;
        else 
            if (!isFileOutput && !canRead(filePath))
                cout << "Error, no access to read the file." << endl;
            else 
                if (isFileOutput && !canWrite(filePath))
                    cout << "Error, no access to write into the file." << endl;
                else
                {
                    checkInput = true;
                    cout << "Assigning is completed successfully." << endl;
                }
    
    testFile.close();
    return checkInput;
}

bool workWithConsoleOrFile(bool isOutput)
{
    int number;
    bool isFromFile;

    number = 0;
    isFromFile = false;

    if (isOutput)
        cout << "If data is output to the console write 0, if from file write 1." << endl;
    else
        cout << "If data is entered from the console write 0, if from file write 1." << endl;

    number = readAndVerify(0, 1, "> ");

    if (number == 1)
        isFromFile = true;
    else
        isFromFile = false;

    if (isFromFile)
        if (isOutput)
            cout << "The data is output to a file." << endl;
        else
            cout << "The data is entered from a file." << endl;
    else 
        if (isOutput)
            cout << "The data is output to the console." << endl;
        else
            cout << "The data is entered from the console." << endl;

    return isFromFile;
}

int readIntegerFromFile(const int MIN_NUMBER, const int MAX_NUMBER, string filePath)
{
    const int MIN_LENGTH = 0;
    const int MAX_LENGTH = 1000000;

    ifstream inputFile;
    int number;

    number = 0;

    inputFile.open(filePath);
    
    if (inputFile.eof())
    {
        cout << "Error, file is empty" << endl;
        number = 0;
    }
    else
    {
        inputFile >> number;
        if (number < MIN_LENGTH || number > MAX_LENGTH)
        {
            cout << "Incorrect number, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
            number = 0;
        }
        else
        {
            if (inputFile.fail())
                number = 0;
        }
    }

    inputFile.close();
    return number;
}

int readIntegerFromConsole(const int MIN_NUMBER, const int MAX_NUMBER)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 30;

    int number;
    number = 0;

    number = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write number: ");
    return number;
}

void writeIntegerIntoConsole(int number)
{
    cout << "The result is: " << number << endl;
}

void writeIntegerIntoFile(string &filePath, int number)
{
    ofstream outputFile(filePath);

    if (!outputFile.is_open())
    {
        cout << "Error creating file." << endl;
        return;
    }

    outputFile << "The result is: " << number << endl;

    outputFile.close();
    cout << "Matrix written to file successfully." << endl;
}

string askTheFilePath()
{
    string filePath;
    filePath = "";
    cout << "Write the existing file path: ";
    cin >> filePath;
    return filePath;
}

string assignMyFile(bool isFileOutput)
{
    string filePath;
    bool isIncorrect;

    filePath = "";
    isIncorrect = false;        

    do
    {
        filePath = askTheFilePath();
        isIncorrect = !checkMyFile(filePath, isFileOutput);
    } while (isIncorrect);

    return filePath;
}

void readingStage(int &number) 
{
    const int MIN_NUMBER = -100000;
    const int MAX_NUMBER = 100000;

    bool isFromFile, isAllUndone, isOutput;
    string filePath;

    isFromFile = workWithConsoleOrFile(false);
    isOutput = false;

    if (isFromFile)
    {
        isAllUndone = true;
        do
        {
            filePath = assignMyFile(isOutput);
            number = readIntegerFromFile(MIN_NUMBER, MAX_NUMBER, filePath);

            if (number == 0)
                cout << "There is might be error with reading, bad file read or file is not open for reading." << endl;
            else
                isAllUndone = false;

        } while (isAllUndone);
    }
    else
        number = readIntegerFromConsole(MIN_NUMBER, MAX_NUMBER);
}

void writingStage(int &number)
{
    bool isAllUndone, isOutput, isToFile;
    string filePath;

    isToFile = workWithConsoleOrFile(true);
    isOutput = true;

    if (isToFile)
    {
        filePath = assignMyFile(isOutput);
        writeIntegerIntoFile(filePath, number);
    }
    else
        writeIntegerIntoConsole(number);
}

int main()
{
    int number;

    number = 0;
    
    writePurpose();
    readingStage(number);
    writingStage(number);

    return 0;
}