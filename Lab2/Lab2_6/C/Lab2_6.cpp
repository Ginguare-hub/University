#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writePurpose() 
{
    cout << "Program finds amicable numbers lower than 100000." << endl;
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

bool checkMyFile(string filePath)
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
            if (!canWrite(filePath))
                cout << "Error, no access to write into the file." << endl;
            else
            {
                checkInput = true;
                cout << "Assigning is completed successfully." << endl;
            }
    
    testFile.close();
    return checkInput;
}

bool workWithConsoleOrFile()
{
    int number;
    bool isFromFile;

    number = 0;
    isFromFile = false;

    cout << "If data is output to the console write 0, if from file write 1." << endl;
    number = readAndVerify(0, 1, "> ");

    if (number == 1)
        isFromFile = true;
    else
        isFromFile = false;

    if (isFromFile)
        cout << "The data is output to a file." << endl;
    else 
        cout << "The data is output to the console." << endl;

    return isFromFile;
}

string askTheFilePath()
{
    string filePath;
    filePath = "";
    cout << "Write the existing file path: ";
    cin >> filePath;
    return filePath;
}

string assignMyFile()
{
    string filePath;
    bool isIncorrect;

    filePath = "";
    isIncorrect = false;        

    do
    {
        filePath = askTheFilePath();
        isIncorrect = !checkMyFile(filePath);
    } while (isIncorrect);

    return filePath;
}

int sumOfProperDivisors(int number) 
{
    int i, sumOfDivisors, numberDivTwo;

    i = 0;
    sumOfDivisors = 0;
    numberDivTwo = number / 2 + 1;

    for (i = 1; i < numberDivTwo; i++)
        if (number % i == 0)
            sumOfDivisors = sumOfDivisors + i;

    return sumOfDivisors;
} 

void findAnbicableNumbersConsole()
{
    const int MY_LIMIT = 100001;

    int i, j, sumOfDivisors;

    i, sumOfDivisors = 0;
    j = 1;

    for (i = 1; i < MY_LIMIT; i++)
    {
        sumOfDivisors = sumOfProperDivisors(i);
        if ((i < sumOfDivisors) && (i == sumOfProperDivisors(sumOfDivisors)))
        {
            cout << j << ".  " << i << " And " << sumOfDivisors << endl;
            j++; 
        }
    }
}

void findAnbicableNumbersFile(string filePath)
{
    const int MY_LIMIT = 100001;

    int i, j, sumOfDivisors;
    ofstream outputFile; 

    i, sumOfDivisors = 0;
    j = 1;

    outputFile.open(filePath);

    outputFile << "Ambicable numbers lower than 100000: " << endl;

    for (i = 1; i < MY_LIMIT; i++)
    {
        sumOfDivisors = sumOfProperDivisors(i);
        if ((i < sumOfDivisors) && (i == sumOfProperDivisors(sumOfDivisors)))
        {
            outputFile << j << ".  " << i << " And " << sumOfDivisors << endl;
            j++; 
        }
    }

    outputFile.close();
}

void writingStage()
{
    bool isToFile;
    string filePath;

    isToFile = workWithConsoleOrFile();

    if (isToFile)
    {
        filePath = assignMyFile();
        cout << "Do not open the file before messege about algorithm is done is not arrived." << endl;
        findAnbicableNumbersFile(filePath);
        cout << "Program is completed. File can be opened." << endl;
    }
    else
    {
        findAnbicableNumbersConsole();
        cout << "Program is completed." << endl;
    }
}

int main() 
{
    writePurpose();
    writingStage();
    return 0;
}