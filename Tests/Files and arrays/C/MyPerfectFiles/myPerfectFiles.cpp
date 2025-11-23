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
    else if (isOutput)
        cout << "The data is output to the console." << endl;
    else
        cout << "The data is entered from the console." << endl;

    return isFromFile;
}

int **createMatrix(int &size)
{
    int **matrix;

    matrix = new int *[size];

    for (int i = 0; i < size; i++)
        matrix[i] = new int[size];

    return matrix;
}

void deleteMatrix(int **&matrix, int size)
{
    for (int i = 0; i < size; i++)
        delete[] matrix[i];

    delete[] matrix;
}

// bool checkMatrixFromFile(int MIN_NUMBER, int MAX_NUMBER, const string &filePath, int &matrixSize)
// {
//     const int MIN_LENGTH = 1;
//     const int MAX_LENGTH = 30;

//     int matrixSizeF;
//     bool answer;
//     ifstream inputFile;
//     answer = true;

//     inputFile.open(filePath);

//     if (!inputFile.is_open())
//     {
//         cout << "Error opening file." << endl;
//         answer = false;
//     }

//     inputFile >> matrixSizeF;

//     if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH)
//     {
//         cout << "Incorrect matrix length, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
//         answer = false;
//         inputFile.close();
//     }

//     inputFile.close();

//     return answer;
// }

int **readMatrixFromFile(const int MIN_NUMBER, const int MAX_NUMBER, string filePath, int &matrixSize)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 20;

    ifstream inputFile;
    int **matrix;
    int i, j;

    matrixSize = 0;
    i, j = 0;

    inputFile.open(filePath);

    inputFile >> matrixSize;

    if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH)
    {
        cout << "Incorrect matrix length, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
        delete[] matrix;
        matrix = 0;
    }
    else
    {
        matrix = createMatrix(matrixSize);

        for (i = 0; i < matrixSize; i++)
            for (j = 0; j < matrixSize; j++)
                inputFile >> matrix[i][j];
    }

    if (!inputFile.good())
    {
        cout << "Error with reading matrix data, bad file read." << endl;
        delete[] matrix;
        matrix = 0;
    }

    inputFile.close();
    return matrix;
}

bool isFileNotEmpty(string filePath)
{
    bool isFileNotEmpty;
    ifstream testFile(filePath);

    // if (!testFile.is_open()) {
    //     return false;
    // }

    isFileNotEmpty = true;

    testFile.get();

    if (testFile.eof())
        isFileNotEmpty = false;

    testFile.close();

    return isFileNotEmpty;
}

int main()
{
    const int ERROR_NUMBER = 37707;
    const int MIN_NUMBER = -10000;
    const int MAX_NUMBER = 10000;

    bool isFromFile, isToFile, isAllUndone, i;
    int **matrix;
    int matrixSize;
    string filePath;
    ifstream testFile;

    isFromFile = false;
    isToFile = false;
    matrixSize = 0;

    cout << isFileNotEmpty("C:\\Users\\Vlad\\Desktop\\MyFile1.txt");

    // deleteMatrix(matrix, matrixSize);
    return 0;
}
