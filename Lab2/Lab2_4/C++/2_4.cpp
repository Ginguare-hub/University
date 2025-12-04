#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writePurpose()
{
    cout << "Convert a number from base (2, 8, 10) to base-16 numeral system." << endl;
}

long readAndVerify(const long MIN_NUMBER, const long MAX_NUMBER, string myString)
{
    bool isIncorrect;
    long number;

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

bool isFileNotEmpty(string filePath)
{
    bool isNotEmpty;
    ifstream testFile;

    isNotEmpty = false;

    testFile.open(filePath);

    if (testFile.is_open() && testFile.peek() != ifstream::traits_type::eof())
        isNotEmpty = true;

    testFile.close();
    return isNotEmpty;
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
        cout << "Error, file with path <" << filePath << "> is not exists." << endl;
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
                    if (!isFileOutput && !isFileNotEmpty(filePath))
                        cout << "Error, file is empty." << endl;
                    else
                    {
                        checkInput = true;
                        cout << "Assigning is completed successfully." << endl;
                    }

    testFile.close();
    return checkInput;
}

bool checkIsNumberValid(long number, const long BASE)
{
    bool isValid;

    isValid = true;

    while ((number > 0) && isValid)
    {
        if ((number % 10 > BASE) || (number % 10 == BASE))
            isValid = false;
        number = number / 10;
    }
    return isValid;
}

int readAndVerifyBase(string myString)
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

        if (!isIncorrect && (number != 2) && (number != 8) && (number != 10))
        {
            isIncorrect = true;
            cout << "The number must be equals to 2, 8 or 10." << endl;
        }

    } while (isIncorrect);

    return number;
}

long readAndVerifyForConversion(const long MIN_NUMBER, const long BASE, string myString)
{
    const long MAX_BINARY  = 111111111;
    const long MAX_OCTAL   = 777777;
    const long MAX_DECIMAL = 524286;

    bool isIncorrect;
    long number;
    long localMaxNumber;

    isIncorrect = false;
    localMaxNumber = 0;
    number = 0;

    if (BASE == 2)
        localMaxNumber = MAX_BINARY;
    else 
        if (BASE == 8)
            localMaxNumber = MAX_OCTAL;
        else
            localMaxNumber = MAX_DECIMAL;

    do
    {
        isIncorrect = false;

        number = readAndVerify(0, localMaxNumber, myString);

        if (!checkIsNumberValid(number, BASE))
        {
            cout << "Every digit must not be equal or higher than " << BASE << "." << endl;
            isIncorrect = true;
        }

    } while (isIncorrect);

    return number;
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

long getNumberOfDigits(long number)
{
    int answer;
    answer = 0;

    if (number == 0)
        answer = 1;
    else
        while (number != 0)
        {
            number = number / 10;
            answer = answer + 1;
        }

    return answer;
}

long powerOfTwo(int power)
{
    int i;
    int answer;

    i = 0;
    answer = 1;

    for (i = 1; i <= power; i++)
        answer = answer * 2;

    return answer;
}

char tetradeToHexadecimal(int tetrade)
{
    const int ARRAY_LENGTH = 16;
    char* cArray;
    long answer;
    int i;

    answer = 0;
    i = 0;

    cArray = new char[ARRAY_LENGTH] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    while (tetrade != 0)
    {
        answer = answer + (tetrade % 10) * powerOfTwo(i);
        tetrade = tetrade / 10;
        i++;
    }

    return cArray[answer];
}

char *binaryToHexadecimal(long bNumber, int &arrayLength)
{
    const int H_NUMBER = 10000;
    const int BASE_B = 2;

    int counter;
    long tetrade;
    long aLength;
    char *answerArray;

    counter = 0;
    tetrade = 0;
    aLength = 0;
    answerArray = nullptr;

    aLength = 0;

    if (checkIsNumberValid(bNumber, BASE_B))
    {

        aLength = getNumberOfDigits(bNumber) / 4;

        if ((getNumberOfDigits(bNumber) % 4) > 0)
            aLength = aLength + 1;

        counter = 0;

        answerArray = new char[aLength];
        arrayLength = aLength;

        if (bNumber != 0)
            while (bNumber != 0)
            {
                tetrade = bNumber % H_NUMBER;
                bNumber = bNumber / H_NUMBER;
                answerArray[counter] = tetradeToHexadecimal((int)tetrade);

                counter = counter + 1;
            }
        else 
            if (bNumber == 0)
                answerArray[counter] = tetradeToHexadecimal(0);
    }
    else
        answerArray = nullptr;

    return answerArray;
}

long octalToBinary(long oNumber)
{
    const int BASE_O = 8;
    const int O_NUMBER = 1000;

    long digit;
    long n;
    long answer;
    int* transformArray;

    digit = 0;
    answer = 0;
    n = 1;

    transformArray = new int[BASE_O] {0, 1, 10, 11, 100, 101, 110, 111};

    if (checkIsNumberValid(oNumber, BASE_O))
    {
        while (oNumber != 0)
        {
            digit = oNumber % 10;
            oNumber = oNumber / 10;
            answer = answer + n * transformArray[(int)digit];
            n = n * O_NUMBER;
        }
    }
    return answer;
}

long decimalToBinary(long dNumber)
{
    const int BASE_B = 2;
    const int ARRAY_LENGTH = 64;

    long reverseAnswerArray[ARRAY_LENGTH];
    int i;
    int highArray;
    long answer;

    i = 0;
    answer = 0;

    for (i = 0; i < ARRAY_LENGTH; i++)
        reverseAnswerArray[i] = 0;

    i = 0;

    while (dNumber > 0)
    {
        reverseAnswerArray[i] = dNumber % BASE_B;
        dNumber = dNumber / BASE_B;
        i++;
    }

    highArray = ARRAY_LENGTH - 1;
    for (i = highArray; i >= 0; i--)
        answer = answer * 10 + reverseAnswerArray[i];

    return answer;
}

void reverseArray(char *arrayA, int arrayLength)
{
    int i;
    int halfHigh;
    char temp;

    i = 0;
    halfHigh = arrayLength / 2;

    for (i = 0; i < halfHigh; i++)
    {
        temp = arrayA[i];
        arrayA[i] = arrayA[arrayLength - 1 - i];
        arrayA[arrayLength - 1 - i] = temp;
    }
}

void writeOutArray(char *arrayA, int arrayLength)
{
    int i;
    i = 0;
    cout << "The answer is: ";
    for (i = 0; i < arrayLength; i++)
        cout << arrayA[i];
    cout << endl;
}

char *octalToHexadecimal(long number, int &arrayLength)
{
    long bNumber;
    char *answerArray;

    bNumber = 0;
    answerArray = nullptr;

    bNumber = octalToBinary(number);
    answerArray = binaryToHexadecimal(bNumber, arrayLength);

    return answerArray;
}

char *decimalToHexadecimal(long number, int &arrayLength)
{
    long bNumber;
    char *answerArray;

    bNumber = 0;
    answerArray = nullptr;

    bNumber = decimalToBinary(number);
    answerArray = binaryToHexadecimal(bNumber, arrayLength);

    return answerArray;
}

char *convertNumber(long number, long base, int &arrayLength)
{
    char *answerArray;

    answerArray = nullptr;

    if (base == 2)
        answerArray = binaryToHexadecimal(number, arrayLength);
    else 
        if (base == 8)
            answerArray = octalToHexadecimal(number, arrayLength);
        else
            answerArray = decimalToHexadecimal(number, arrayLength);

    return answerArray;
}

int *readBaseAndNumberFromFile(string filePath, ifstream &inputFile)
{
    const int ARRAY_LENGTH = 2;
    int *shortArray;

    shortArray = nullptr;

    inputFile.open(filePath);

    shortArray = new int[ARRAY_LENGTH];

    inputFile >> shortArray[0];
    inputFile >> shortArray[1];

    if (inputFile.fail())
    {
        cout << "Incorrect numeric data: matrix element." << endl;
        delete[] shortArray;
        shortArray = nullptr;
    }
    if (shortArray != nullptr && ((shortArray[0] != 2) && (shortArray[0] != 8) && (shortArray[0] != 10)))
    {
        cout << "The base must be equals to 2, 8 or 10." << endl;
        delete[] shortArray;
        shortArray = nullptr;
    }
    if ((shortArray != nullptr) && (!checkIsNumberValid(shortArray[1], shortArray[0])))
    {
        cout << "Error, incorrect matrix data." << endl;
        delete[] shortArray;
        shortArray = nullptr;
    }
    inputFile.close();
    return shortArray;
}


void writeNumberIntoFile(string &filePath, char *answerArray, int arrayLength)
{
    ofstream outputFile;
    int i;
    
    i = 0;
    
    outputFile.open(filePath);
    
    if (!outputFile.is_open())
    {
        cout << "The unexpected error is found." << endl;
    }
    else
    {
        outputFile << "The answer is: ";
        reverseArray(answerArray, arrayLength);
        
        for (i = 0; i < arrayLength; i++)
        outputFile << answerArray[i];
        
        outputFile.close();
        cout << "Number written to file successfully." << endl;
    }
}

char *readingStage(int &arrayLength)
{
    char *answerArray;
    bool isFromFile, isOutput, isAllUndone;
    long base, numberBefConv;
    int *dataArray;
    string filePath;
    ifstream inputFile;

    isOutput = false;
    isAllUndone = true;
    base = 0;
    numberBefConv = 0;
    dataArray = nullptr;
    answerArray = nullptr;
    filePath = "";

    isFromFile = workWithConsoleOrFile(isOutput);

    if (isFromFile)
    {
        isAllUndone = true;
        do
        {
            filePath = assignMyFile(isOutput);
            dataArray = readBaseAndNumberFromFile(filePath, inputFile);

            if (dataArray == nullptr)
            {
                cout << "Something went wrong, try again." << endl;
            }
            else
            {
                base = dataArray[0];
                numberBefConv = dataArray[1];
                answerArray = convertNumber(numberBefConv, base, arrayLength);
                isAllUndone = false;
                delete[] dataArray;
            }

        } while (isAllUndone);
    }
    else
    {
        base = readAndVerifyBase("Write the base of number: ");
        numberBefConv = readAndVerifyForConversion(0, base, "Write number that will be converted: ");
        answerArray = convertNumber(numberBefConv, base, arrayLength);
    }

    return answerArray;
}

void writingStage(char *answerArray, int arrayLength)
{
    bool isOutput, isToFile;
    string filePath;

    isToFile = false;
    isOutput = true;
    filePath = "";

    isToFile = workWithConsoleOrFile(isOutput);

    if (isToFile)
    {
        filePath = assignMyFile(isOutput);
        writeNumberIntoFile(filePath, answerArray, arrayLength);
    }
    else
    {
        reverseArray(answerArray, arrayLength);
        writeOutArray(answerArray, arrayLength);
    }
}

void deleteArray(char* myArray)
{
    if (myArray != nullptr)
        delete[] myArray;
}

int main()
{
    char *myArray;
    int arrayLength;

    myArray = nullptr;
    arrayLength = 0;

    writePurpose();
    myArray = readingStage(arrayLength);
    writingStage(myArray, arrayLength);
    deleteArray(myArray);

    return 0;
}