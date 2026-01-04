#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

void writePurpose()
{
    cout << "The program replaces given separators with '+' and calculates the sum of numbers in the string." << endl;
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

string* createStringArray(int size)
{
    string* array1;

    array1 = nullptr;
    array1 = new string[size];

    return array1;
}

void deleteStringArray(string*& array1)
{
    if (array1 != nullptr)
    {
        delete[] array1;
        array1 = nullptr;
    }
}

string* splitString(const string& str, int& count)
{
    stringstream ss(str);
    string word;
    string tempStr;
    string* answerArray;
    int i;

    answerArray = nullptr;
    count = 0;
    i = 0;

    tempStr = str;
    stringstream ssCount(tempStr);

    while (ssCount >> word)
        count++;

    if (count == 0)
        return nullptr;

    answerArray = createStringArray(count);

    stringstream ssCopy(str);
    i = 0;
    while (ssCopy >> word)
    {
        answerArray[i] = word;
        i++;
    }

    return answerArray;
}

bool checkIsStringValid(const string& givenString)
{
    int i;
    bool isValid;

    i = 0;
    isValid = true;

    if (givenString.empty())
    {
        isValid = false;
    }
    else
    {
        if (!isdigit(givenString[0]) && givenString[0] != '+' && givenString[0] != '-')
            isValid = false;

        if (isValid && !isdigit(givenString[givenString.length() - 1]))
            isValid = false;

        if (isValid)
        {
            i = 0;
            while (i < givenString.length() - 1 && isValid)
            {
                char c = givenString[i];
                char nextC = givenString[i + 1];

                if (c == '+' && nextC == '+')
                    isValid = false;

                if (!isdigit(c) && c != '+' && c != '-' && c != '.' && c != ',')
                    isValid = false;

                i++;
            }
        }
    }

    if (!isValid)
        cout << "The string contains invalid characters or their position is incorrect." << endl;

    return isValid;
}

string findSumFromString(const string& givenString)
{
    stringstream ss(givenString);
    string token;
    string answerString;
    double sum;
    double number;
    bool isFine;
    bool hasNumbers;
    char* endPtr;
    int i;

    sum = 0.0;
    number = 0.0;
    isFine = true;
    hasNumbers = false;
    endPtr = nullptr;
    answerString = "";

    isFine = checkIsStringValid(givenString);

    if (isFine)
    {
        string modifiedString = givenString;
        stringstream ssCopy(modifiedString);
        string tempToken;

        while (getline(ssCopy, tempToken, '+'))
        {
            if (!tempToken.empty())
            {
                for (i = 0; i < tempToken.length(); i++)
                {
                    if (tempToken[i] == ',')
                        tempToken[i] = '.';
                }

                number = strtod(tempToken.c_str(), &endPtr);

                if (endPtr == tempToken.c_str() || *endPtr != '\0')
                {
                    cout << "Error with number conversion." << endl;
                    isFine = false;
                }
                else
                {
                    sum += number;
                    hasNumbers = true;
                }
            }
        }
    }

    if (!isFine)
        answerString = "";
    else if (!hasNumbers)
        answerString = "There are no correct numbers in the line.";
    else
        answerString = givenString + "=" + to_string(sum);

    return answerString;
}

string findAnswerString(string* arrayOfSeparators, int arrayLength, string givenString)
{
    string answerString;
    int i;
    size_t pos;

    i = 0;
    pos = 0;
    answerString = "";

    if (arrayOfSeparators != nullptr && arrayLength > 0)
    {
        i = 0;
        while (i < arrayLength)
        {
            string separator = arrayOfSeparators[i];
            pos = 0;

            while ((pos = givenString.find(separator, pos)) != string::npos)
            {
                givenString.replace(pos, separator.length(), "+");
                pos += 1;
            }

            i++;
        }
    }

    answerString = findSumFromString(givenString);

    return answerString;
}

string* readSeparatorsFromFile(string filePath, int& arrayLength, string& givenString)
{
    ifstream inputFile(filePath);
    string line;
    string* arrayOfSeparators;
    bool isFine;
    int expectedLength;
    int readLength;

    arrayOfSeparators = nullptr;
    arrayLength = 0;
    isFine = true;
    expectedLength = 0;
    readLength = 0;

    if (!getline(inputFile, line))
    {
        cout << "Error, file is empty" << endl;
        isFine = false;
    }

    if (isFine)
    {
        stringstream ss(line);
        if (!(ss >> expectedLength) || expectedLength < 1 || expectedLength > 100)
        {
            cout << "Incorrect length, the number must fit the range [1,100]." << endl;
            isFine = false;
        }
    }

    if (isFine)
    {
        if (!getline(inputFile, line))
        {
            cout << "Incorrect numeric data: array element." << endl;
            isFine = false;
        }
    }

    if (isFine)
    {
        arrayOfSeparators = splitString(line, readLength);
        if (arrayOfSeparators == nullptr || readLength != expectedLength)
        {
            cout << "Incorrect separators data." << endl;
            deleteStringArray(arrayOfSeparators);
            arrayOfSeparators = nullptr;
            isFine = false;
        }
        else
        {
            arrayLength = readLength;
        }
    }

    if (isFine)
    {
        if (!getline(inputFile, givenString))
        {
            cout << "Incorrect data: string." << endl;
            givenString = "";
        }
    }

    inputFile.close();

    return arrayOfSeparators;
}

string* readSeparatorsFromConsole(int& arrayLength, string& givenString)
{
    string* arrayOfSeparators;
    int i;

    arrayOfSeparators = nullptr;
    i = 0;
    arrayLength = 0;

    cout << "The length of the separators should decrease with increasing order." << endl;
    arrayLength = readAndVerify(1, 100, "Write amount of separators: ");

    arrayOfSeparators = createStringArray(arrayLength);

    i = 0;
    while (i < arrayLength)
    {
        cout << "Write separator with index [" << i << "] : ";
        cin >> arrayOfSeparators[i];
        i++;
    }

    cout << "Write the string of numbers between separators." << endl;
    cin.ignore();
    getline(cin, givenString);

    return arrayOfSeparators;
}

void readingStage(string*& arrayOfSeparators, int& arrayLength, string& givenString)
{
    bool isFromFile;
    string filePath;
    bool isAllUndone;

    isFromFile = false;
    isAllUndone = true;

    isFromFile = workWithConsoleOrFile(false);

    arrayOfSeparators = nullptr;
    arrayLength = 0;
    givenString = "";

    if (isFromFile)
    {
        isAllUndone = true;

        while (isAllUndone)
        {
            filePath = assignMyFile(false);
            deleteStringArray(arrayOfSeparators);
            arrayOfSeparators = readSeparatorsFromFile(filePath, arrayLength, givenString);

            if (arrayOfSeparators == nullptr)
                cout << "Error with reading data, bad file read." << endl;
            else
                isAllUndone = false;
        }
    }
    else
    {
        arrayOfSeparators = readSeparatorsFromConsole(arrayLength, givenString);
    }
}

void writingStage(const string& answerString)
{
    bool isToFile;
    string filePath;

    isToFile = workWithConsoleOrFile(true);

    if (isToFile)
    {
        filePath = assignMyFile(true);

        ofstream outputFile(filePath);
        if (!outputFile.is_open())
        {
            cout << "Error creating file." << endl;
        }
        else
        {
            outputFile << answerString << endl;
            outputFile.close();
            cout << "Answer written to file successfully." << endl;
        }
    }
    else
    {
        cout << answerString << endl << endl;
    }
}

int main()
{
    string* arrayOfSeparators;
    int arrayLength;
    string givenString;
    string answerString;

    arrayOfSeparators = nullptr;
    arrayLength = 0;
    givenString = "";
    answerString = "";

    writePurpose();
    readingStage(arrayOfSeparators, arrayLength, givenString);
    answerString = findAnswerString(arrayOfSeparators, arrayLength, givenString);
    writingStage(answerString);

    deleteStringArray(arrayOfSeparators);
    return 0;
}