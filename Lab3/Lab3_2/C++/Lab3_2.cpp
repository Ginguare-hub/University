#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

void writePurpose() 
{
    cout << "The program generates two sets, the first of which contains all prime numbers from the given set, and the second of which contains all composite numbers." << endl;
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
    bool canWriteFile;
    
    canWriteFile = false;
    
    outputFile.open(filePath, ios::app);
    canWriteFile = outputFile.is_open();
    outputFile.close();

    outputFile.close(); 
    return canWriteFile;
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

set<int> readSetFromFile(const int MIN_NUMBER, const int MAX_NUMBER, string filePath)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 10000;

    ifstream inputFile;
    set<int> mySet;
    int i, mySetLength, setElement;
    bool isFine;

    mySetLength = 0;
    i = 0;
    setElement = 0;
    isFine = true;

    inputFile.open(filePath);

    inputFile >> mySetLength;

    if (inputFile.eof())
    {
        cout << "Error, file is empty" << endl;
        mySet.clear();
        isFine = false;
    }

    if (isFine)
    {
        if ((mySetLength < MIN_LENGTH) || (mySetLength > MAX_LENGTH))
        {
            cout << "Incorrect set length, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
            mySet.clear();
            isFine = false;
        }
    }

    if (isFine)
    {
        for (i = 0; i < mySetLength; i++)
        {
            inputFile >> setElement;
            
            if (inputFile.fail())
            {
                mySet.clear();
                isFine = false;
                cout << "Incorrect numeric data: set element." << endl;
            }
            
            if (isFine)
                mySet.insert(setElement);
        }
    }

    inputFile.close();
    
    if (mySet.empty())
        cout << "Error, incorrect set data." << endl;

    return mySet;
}

set<int> readSetFromConsole(const int MIN_NUMBER, const int MAX_NUMBER)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 1000;

    set<int> set1;
    int i, setLength, setElement;

    set1.clear();
    i = 0;
    setLength = 0;
    setElement = 0;

    setLength = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write set length: ");

    for (i = 0; i < setLength; i++)
    {
        cout << "Write element of set: ";
        setElement = readAndVerify(MIN_NUMBER, MAX_NUMBER, "");
        set1.insert(setElement);
    }

    return set1;
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

void writeSetIntoFile(string &filePath, set<int> setOfPrime, set<int> setOfNonPrime)
{
    ofstream outputFile;
    bool isReady;

    isReady = true;
    
    outputFile.open(filePath);

    if (!outputFile.is_open())
    {
        cout << "The unexpected error is found." << endl;
        isReady = false;
    }

    if (isReady)
    {
        if (setOfPrime.empty())
        outputFile << "There is no prime numbers in given set." << endl;
        else
        {
            outputFile << "The result elements of set with prime numbers is: " << endl;
            for (int element: setOfPrime)
                outputFile << element << " ";
        }

        outputFile << endl;

        if (setOfNonPrime.empty())
            outputFile << "There is no non-prime numbers in given set." << endl;
        else
        {
            outputFile << "The result elements of set with non-prime numbers is: " << endl;
            for (int element: setOfNonPrime)
                outputFile << element << " ";
        }
    }

    outputFile.close();
}

void writeSetIntoConsole(set<int> setOfPrime, set<int> setOfNonPrime)
{
    if (setOfPrime.empty())
        cout << "There is no prime numbers in given set." << endl;
    else
    {
        cout << "The result elements of set with prime numbers is: " << endl;
        for (int element: setOfPrime)
            cout << element << " ";
    }

    cout << endl;

    if (setOfNonPrime.empty())
        cout << "There is no non-prime numbers in given set." << endl;
    else
    {
        cout << "The result elements of set with non-prime numbers is: " << endl;
        for (int element: setOfNonPrime)
            cout << element << " ";
    }

    cout << endl;
}

bool discoverIsNumberPrime(int number)
{
    int i, numberP1;
    bool isShouldNotStop, isPrime;

    i = 2;
    numberP1 = 0;
    isShouldNotStop = true;
    isPrime = false;

    if (number < 2)
        isPrime = false;
    else
    {
        numberP1 = number - 1;

        for (i = 2; i <= numberP1; i++)
        {
            if ((number % i == 0) && (isShouldNotStop))
            {
                isPrime = false;
                isShouldNotStop = false;
            }
            else
                if (isShouldNotStop)
                    isPrime = true;
        }

        if (number == 2)
            isPrime = true;
    }

    return isPrime;
}

void divideSet(set<int> &givenSet, set<int> &setOfPrime, set<int> &setOfNonPrime)
{
    int setElement;

    setElement = 0;

    for (int setElement: givenSet)
    {  
        if (discoverIsNumberPrime(setElement))
            setOfPrime.insert(setElement);
        else
            setOfNonPrime.insert(setElement);
    }
}

void readingStage(set<int> &set1) 
{
    const int MIN_NUMBER = 0;
    const int MAX_NUMBER = 100000;

    bool isFromFile, isAllDone, isOutput;
    string filePath;

    isOutput = false;
    isAllDone = true;
    isFromFile = false;
    filePath = "";
    
    isFromFile = workWithConsoleOrFile(isOutput);

    if (isFromFile)
    {
        do
        {
            isAllDone = true;
            filePath = assignMyFile(isOutput);
            set1 = readSetFromFile(MIN_NUMBER, MAX_NUMBER, filePath);

            if (set1.empty())
                isAllDone = false;

        } while (!isAllDone);
    }
    else
        set1 = readSetFromConsole(MIN_NUMBER, MAX_NUMBER);
}

void writingStage(set<int> setOfPrime, set<int> setOfNonPrime)
{
    bool isToFile, isOutput;
    string filePath;

    isToFile = false;
    isOutput = true;
    filePath = "";

    isToFile = workWithConsoleOrFile(isOutput);

    if (isToFile)
    {
        filePath = assignMyFile(isOutput);
        writeSetIntoFile(filePath, setOfPrime, setOfNonPrime);
    }
    else
        writeSetIntoConsole(setOfPrime, setOfNonPrime);
}

int main()
{
    set<int> givenSet, setOfPrime, setOfNonPrime;

    writePurpose();
    readingStage(givenSet);
    divideSet(givenSet, setOfPrime, setOfNonPrime);
    writingStage(setOfPrime, setOfNonPrime);

    return 0;
}