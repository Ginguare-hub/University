#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writePurpose()
{
    cout << "Sorts an array using natural merge sorting." << endl;
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

int *createArray(int size)
{
    int *array1;

    array1 = nullptr;
    array1 = new int[size];

    return array1;
}

int *readArrayFromFile(const int MIN_NUMBER, const int MAX_NUMBER, string filePath, int &arraySize)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 100;

    ifstream inputFile;
    int *array1;
    int i;

    arraySize = 0;
    array1 = nullptr;
    i = 0;

    inputFile.open(filePath);
    inputFile >> arraySize;

    if (inputFile.eof())
    {
        cout << "Error, file is empty" << endl;
        array1 = 0;
    }
    else
    {

        if (arraySize < MIN_LENGTH || arraySize > MAX_LENGTH)
        {
            cout << "Incorrect array length, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
            array1 = 0;
        }
        else
        {
            array1 = createArray(arraySize);

            for (i = 0; i < arraySize; i++)
                inputFile >> array1[i];

            if (inputFile.fail())
            {
                delete[] array1;
                array1 = 0;
            }
        }
    }

    inputFile.close();
    return array1;
}

int *readArrayFromConsole(const int MIN_NUMBER, const int MAX_NUMBER, int &arraySize)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 100;

    int *array1;
    int i;

    array1 = nullptr;
    i = 0;

    arraySize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write array length: ");
    array1 = createArray(arraySize);

    for (i = 0; i < arraySize; i++)
    {
        cout << "Write element [" << i << "] of array: ";
        array1[i] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "");
    }

    return array1;
}

void writeArrayIntoFile(string &filePath, int *array1, int size)
{
    ofstream outputFile(filePath);
    int i;
    bool isReady;

    isReady = true;

    if (!outputFile.is_open())
    {
        cout << "Error creating file." << endl;
        isReady = false;
    }

    if (isReady)
    {
        outputFile << "The result array is: " << endl;
        for (i = 0; i < size; i++)
        {
            outputFile << array1[i] << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    cout << "Array written to file successfully." << endl;
}

void writeArrayIntoConsole(int *array, int size)
{
    int i;

    cout << "The result array is: " << endl;
    for (i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void merge(int array1[], int size1, int array2[], int size2, int *&answerArray, int &answerSize)
{
    int i, j, index;

    i = 0;
    j = 0;
    index = 0;

    answerSize = size1 + size2;
    answerArray = createArray(answerSize);

    while (i < size1 && j < size2)
    {
        if (array1[i] <= array2[j])
        {
            answerArray[index] = array1[i];
            i++;
        }
        else
        {
            answerArray[index] = array2[j];
            j++;
        }
        index++;
    }

    while (i < size1)
    {
        answerArray[index] = array1[i];
        i++;
        index++;
    }

    while (j < size2)
    {
        answerArray[index] = array2[j];
        j++;
        index++;
    }
}

void copyArray(int source[], int *&dest, int size)
{
    int i;
    i = 0;

    dest = createArray(size);

    for (i = 0; i < size; i++)
    {
        dest[i] = source[i];
    }
}

void copyArrayPart(int source[], int startIndex, int count, int *&dest)
{
    int i;

    i = 0;

    dest = createArray(count);

    for (i = 0; i < count; i++)
    {
        dest[i] = source[startIndex + i];
    }
}

void sortArray(int *&givenArray, int arraySize)
{
    int i, j, k, l, arrayLength, amountOfMerges, size1, size2, size3, mergedSize;
    int *array1, *array2, *array3, *arrayOfLabelIndices, *newArray, *mergedArray;

    i = 0;
    j = 0;
    k = 0;
    arrayLength = 0;
    amountOfMerges = 0;
    size1 = 0;
    size2 = 0;
    size3 = 0;
    mergedSize = 0;
    array1 = nullptr;
    array2 = nullptr;
    array3 = nullptr;
    arrayOfLabelIndices = nullptr;
    newArray = nullptr;
    mergedArray = nullptr;

    copyArray(givenArray, newArray, arraySize);

    arrayLength = 1;

    while (arrayLength != 0)
    {
        i = 0;
        j = 0;
        k = 0;
        l = 0;
        arrayLength = 0;

        while (i < arraySize - 1)
        {
            if (givenArray[i] > givenArray[i + 1])
            {
                arrayLength++;
            }
            i++;
        }

        if (arrayLength > 0)
        {
            arrayOfLabelIndices = createArray(arrayLength);
            i = 0;

            while (i < arraySize - 1)
            {
                if (givenArray[i] > givenArray[i + 1])
                {
                    arrayOfLabelIndices[j] = i;
                    j++;
                }
                i++;
            }

            amountOfMerges = (arrayLength + 1) / 2;

            for (i = 0; i < amountOfMerges; i++)
            {
                if (i == 0)
                {
                    size1 = arrayOfLabelIndices[i] + 1;
                    copyArrayPart(givenArray, 0, size1, array1);
                }
                else
                {
                    size1 = arrayOfLabelIndices[i] - arrayOfLabelIndices[i - 1];
                    copyArrayPart(givenArray, arrayOfLabelIndices[i - 1] + 1, size1, array1);
                }

                if (i == 0)
                {
                    size2 = arraySize - arrayOfLabelIndices[arrayLength - 1] - 1;
                    copyArrayPart(givenArray, arrayOfLabelIndices[arrayLength - 1] + 1, size2, array2);
                }
                else
                {
                    size2 = arrayOfLabelIndices[arrayLength - i] - arrayOfLabelIndices[arrayLength - i - 1];
                    copyArrayPart(givenArray, arrayOfLabelIndices[arrayLength - i - 1] + 1, size2, array2);
                }

                if ((arrayLength % 2 == 0) && (i == 0))
                {
                    size3 = arrayOfLabelIndices[arrayLength / 2] - arrayOfLabelIndices[arrayLength / 2 - 1];
                    copyArrayPart(givenArray, arrayOfLabelIndices[arrayLength / 2 - 1] + 1, size3, array3);
                }

                merge(array1, size1, array2, size2, mergedArray, mergedSize);

                for (l = 0; l < mergedSize; l++)
                {
                    newArray[k] = mergedArray[l];
                    k++;
                }

                if ((i == (amountOfMerges - 1)) && (arrayLength % 2 == 0))
                {
                    for (l = 0; l < size3; l++)
                    {
                        newArray[k] = array3[l];
                        k++;
                    }
                }

                delete[] array1;
                delete[] array2;
                delete[] mergedArray;
                array1 = nullptr;
                array2 = nullptr;
                mergedArray = nullptr;
            }

            if (arrayLength % 2 == 0)
            {
                delete[] array3;
                array3 = nullptr;
            }

            delete[] arrayOfLabelIndices;
            arrayOfLabelIndices = nullptr;

            delete[] givenArray;
            givenArray = newArray;
            newArray = nullptr;
            copyArray(givenArray, newArray, arraySize);
        }
    }

    delete[] newArray;
}

void readingStage(int *&array1, int &arraySize)
{
    const int MIN_NUMBER = -10000;
    const int MAX_NUMBER = 10000;

    bool isFromFile, isAllUndone, isOutput;
    string filePath;

    isOutput = false;
    isFromFile = workWithConsoleOrFile(isOutput);

    if (isFromFile)
    {
        isAllUndone = true;

        do
        {
            filePath = assignMyFile(isOutput);
            array1 = readArrayFromFile(MIN_NUMBER, MAX_NUMBER, filePath, arraySize);

            if (array1 == 0)
                cout << "Error with reading data, bad file read." << endl;
            else
                isAllUndone = false;

        } while (isAllUndone);
    }
    else
        array1 = readArrayFromConsole(MIN_NUMBER, MAX_NUMBER, arraySize);
}

void writingStage(int *array1, int arraySize)
{
    bool isAllUndone, isOutput, isToFile;
    string filePath;

    isOutput = true;
    isToFile = workWithConsoleOrFile(isOutput);

    if (isToFile)
    {
        filePath = assignMyFile(isOutput);
        writeArrayIntoFile(filePath, array1, arraySize);
    }
    else
        writeArrayIntoConsole(array1, arraySize);
}

int main()
{
    int *array1;
    int arraySize;

    array1 = nullptr;
    arraySize = 0;

    writePurpose();
    readingStage(array1, arraySize);
    sortArray(array1, arraySize);
    writingStage(array1, arraySize);

    delete[] array1;
    return 0;
}