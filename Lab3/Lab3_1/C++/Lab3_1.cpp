#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writePurpose() 
{
    cout << "Extract substring representing an integer from a string containing letters, digits, dots, \"+\" and \"-\"." << endl;
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

string readStringFromFile(string filePath)
{
    ifstream inputFile;
    string str;

    str = "";

    inputFile.open(filePath);
    
    if (inputFile.eof())
    {
        cout << "Error, file is empty" << endl;
        str = "";
    }
    else
    {
        inputFile >> str;

        if (inputFile.fail())
            str = "";
    }

    inputFile.close();
    return str;
}

string readStringFromConsole()
{
    string str;
    str = "";
    cout << "Enter string: ";
    cin >> str;
    return str;
}

void writeResultIntoConsole(string str)
{
    if (str == "") 
    {
        cout << "No valid integer found." << endl;    
    }
    else
        cout << "Extracted integer: " << str << endl;
}

void writeResultIntoFile(string &filePath, string str)
{
    ofstream outputFile(filePath);

    if (!outputFile.is_open())
    {
        cout << "Error creating file." << endl;
        return;
    }

    if (str == "") 
    {
        outputFile << "No valid integer found." << endl;    
    }
    else
        outputFile << "Extracted integer: " << str << endl;

    outputFile.close();
    cout << "Answer written to file successfully." << endl;
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

bool isDigit(char myChar)
{
    bool answer; 
    answer = false;
    
    if (((myChar > '0') || (myChar == '0')) && ((myChar < '9') || (myChar == '9')))
        answer = true;
    
    return answer;
}

string extractInteger(string inputStr)
{
    int i, j;
    string answer;
    bool isNotFound;
    
    i = 0;
    j = 0;
    answer = "";
    isNotFound = true;
    
    while ((i < inputStr.length()) && isNotFound)
    {
        if (((inputStr[i] == '+') || (inputStr[i] == '-')) 
            && (i + 1 < inputStr.length()) && isDigit(inputStr[i + 1]))
        {
            answer = answer + inputStr[i];
            j = i + 1;
            
            while ((j < inputStr.length()) && isNotFound)
            {
                if (isDigit(inputStr[j]))
                    answer = answer + inputStr[j];
                
                if (j == inputStr.length() - 1)
                    isNotFound = false;
                
                if (isNotFound && (j + 1 < inputStr.length()) && isDigit(inputStr[j + 1]))
                {
                    if (j + 1 == inputStr.length() - 1)
                    {
                        answer = answer + inputStr[j + 1];
                        isNotFound = false;
                    }
                }
                else
                    isNotFound = false;
                
                j++;
            }
        }
        i++;
    }
    return answer;
}

void readingStage(string &str) 
{
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
            str = readStringFromFile(filePath);

            if (str == "")
                cout << "There is might be error with reading, bad file read or file is not open for reading." << endl;
            else
                isAllUndone = false;

        } while (isAllUndone);
    }
    else
        str = readStringFromConsole();
}

void writingStage(string &str)
{
    bool isAllUndone, isOutput, isToFile;
    string filePath;

    isToFile = workWithConsoleOrFile(true);
    isOutput = true;

    if (isToFile)
    {
        filePath = assignMyFile(isOutput);
        writeResultIntoFile(filePath, str);
    }
    else
        writeResultIntoConsole(str);
}

int main()
{
    string str;
    str = "";
    
    writePurpose();
    readingStage(str);
    str = extractInteger(str);
    writingStage(str);

    return 0; 
}