#include <iostream>
#include <fstream>
#include <string>

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

    bool isText;
    int index;

    isText = true;
    index = filePath.length();

    if (index < MIN_PATH_LENGTH || filePath.find(".txt") == string::npos)
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
    int startPos, pos, i;
    string* answerArray;

    count = 0;
    pos = 0;
    startPos = 0;
    i = 0;
    answerArray = nullptr;

    pos = 0;
    while (pos < str.length())
    {
        while (pos < str.length() && str[pos] == ' ')
            pos++;

        if (pos < str.length())
        {
            count++;
            
            while (pos < str.length() && str[pos] != ' ')
                pos++;
        }
    }

    if (count == 0)
        answerArray = nullptr;
    else 
    {
        answerArray = createStringArray(count);

        i = 0;
        pos = 0;
        while (pos < str.length())
        {
            while (pos < str.length() && str[pos] == ' ')
                pos++;

            if (pos < str.length())
            {
                startPos = pos;
                while (pos < str.length() && str[pos] != ' ')
                    pos++;

                answerArray[i] = str.substr(startPos, pos - startPos);
                i++;
            }
        }
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
        isValid = false;

    if (isValid)
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
                if ((i + 1 < givenString.length()) && (givenString[i] == '+' && givenString[i + 1] == '+'))
                    isValid = false;

                if (!isdigit(givenString[i]) && givenString[i] != '+' && givenString[i] != '-' && givenString[i] != '.' && givenString[i] != ',')
                    isValid = false;

                i++;
            }
        }
    }

    return isValid;
}

string findSumFromString(const string& givenString)
{
    string answerString, stringPart;
    double sumOfNumbers, number;
    int i, j, partLength, partIndex;
    bool isFine, isThereNumbers, isNumberFull;

    sumOfNumbers = 0.0;
    number = 0.0;
    i = j = partLength = partIndex = 0;
    stringPart = "";
    isFine = true;
    isThereNumbers = false;
    isNumberFull = false;
    answerString = "";

    isFine = checkIsStringValid(givenString);

    if (isFine)
    {
        i = 0;
        partIndex = 0;
        while (i < givenString.length())
        {
            if (givenString[i] == '+' || i == givenString.length() - 1)
            {
                if (i == givenString.length() - 1)
                    partLength = i - partIndex + 1;
                else
                    partLength = i - partIndex;

                stringPart = givenString.substr(partIndex, partLength);

                for (j = 0; j < stringPart.length(); j++)
                {
                    if (stringPart[j] == ',')
                        stringPart[j] = '.';
                }

                try
                {
                    number = stod(stringPart);
                    sumOfNumbers = sumOfNumbers + number;
                    isThereNumbers = true;
                }
                catch (...)
                {
                    cout << "Error with number conversion." << endl;
                    isFine = false;
                }

                partIndex = i + 1;
            }
            i++;
        }
    }

    if (!isFine)
        answerString = "The string contains invalid characters or their position is incorrect.";
    else 
        if (!isThereNumbers)
            answerString = "There are no correct numbers in the line.";
        else
            answerString = givenString + "=" + to_string(sumOfNumbers);

    return answerString;
}

string findAnswerString(string* arrayOfSeparators, int arrayLength, string givenString)
{
    string separator, substring, sumFromString;
    int i, j, lengthOfSeparator, specialLength;

    i = 0;
    j = 0;
    lengthOfSeparator = 0;
    specialLength = 0;
    separator = "";
    substring = "";
    sumFromString = "";

    i = 0;
    while (i < arrayLength)
    {
        separator = arrayOfSeparators[i];
        lengthOfSeparator = separator.length();
        specialLength = givenString.length() - lengthOfSeparator + 1;

        j = 0;
        while (j < specialLength)
        {
            substring = givenString.substr(j, lengthOfSeparator);

            if (substring == separator)
            {
                givenString.erase(j, lengthOfSeparator - 1);
                givenString[j] = '+';
                specialLength = givenString.length() - lengthOfSeparator + 1;
            }
            else
                j++;
        }

        i++;
    }

    sumFromString = findSumFromString(givenString);

    return sumFromString;
}

string* readSeparatorsFromFile(string filePath, int& arrayLength, string& givenString)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 100;

    ifstream inputFile;
    string line;
    string* array1;
    int expectedLength, i;
    bool isFine;

    array1 = nullptr;
    arrayLength = 0;
    expectedLength = 0;
    i = 0;
    isFine = true;
    line = "";

    inputFile.open(filePath);

    if (!getline(inputFile, line))
    {
        cout << "Error, file is empty" << endl;
        isFine = false;
    }

    if (isFine)
    {  
        inputFile >> expectedLength;

        if (inputFile.fail())
        {
            delete[] array1;
            array1 = 0;
            isFine = false;
        }

        if (isFine && (expectedLength < MIN_LENGTH || expectedLength > MAX_LENGTH))
        {
            cout << "Incorrect length, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
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
        array1 = splitString(line, arrayLength);
        if (array1 == nullptr || arrayLength != expectedLength)
        {
            cout << "Incorrect separators data." << endl;
            deleteStringArray(array1);
            array1 = nullptr;
            isFine = false;
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

    if (!isFine && array1 != nullptr)
    {
        deleteStringArray(array1);
    }

    return array1;
}

string* readSeparatorsFromConsole(int& arrayLength, string& givenString)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 100;

    string* array1;
    int i;

    array1 = nullptr;
    i = 0;
    arrayLength = 0;

    cout << "The length of the separators should decrease with increasing order." << endl;
    arrayLength = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write amount of separators: ");

    array1 = createStringArray(arrayLength);

    i = 0;
    while (i < arrayLength)
    {
        cout << "Write separator with index [" << i << "] : ";
        cin >> array1[i];
        i = i + 1;
    }

    cout << "Write the string of numbers between separators." << endl;
    cin.ignore();                   
    getline(cin, givenString);   

    return array1;
}

void readingStage(string*& arrayOfSeparators, int& arrayLength, string& givenString)
{
    bool isFromFile;
    string filePath;
    bool isAllDone;

    isFromFile = false;
    isAllDone = true;
    filePath = "";

    isFromFile = workWithConsoleOrFile(false);

    arrayOfSeparators = nullptr;
    arrayLength = 0;
    givenString = "";

    if (isFromFile)
    {
        do
        {
            isAllDone = true;
            filePath = assignMyFile(false);
            arrayOfSeparators = readSeparatorsFromFile(filePath, arrayLength, givenString);

            if (arrayOfSeparators == nullptr)
            {
                cout << "Error with reading data, bad file read." << endl;
                isAllDone = false;
            }

        } while (!isAllDone);
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
        cout << answerString << endl;
    }
}

int main()
{
    string* arrayOfSeparators;
    int arrayLength;
    string givenString, answerString;

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