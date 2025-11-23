#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// const int ERROR_NUMBER = 37707;

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

// bool isFileNotEmpty(string filePath)
// {
//     bool isFileNotEmpty;
//     ifstream testFile(filePath);

//     // if (!testFile.is_open()) {
//     //     return false;
//     // }

//     isFileNotEmpty = true;

//     if (testFile.eof())
//         isFileNotEmpty = false;

//     testFile.close();

//     return isFileNotEmpty;
// }

// bool isFileNotEmpty(ifstream &inputFile)
// {
//     bool isFileNotEmpty;

//     isFileNotEmpty = true;

//     if (inputFile.eof())
//         isFileNotEmpty = false;

//     return isFileNotEmpty;
// }

bool canRead(string filePath)
{

    bool isReady;
    ifstream testFile(filePath);

    testFile.open(filePath);

    if (testFile.is_open())
    {
        testFile.close();
        isReady = true;
    }
    else
        isReady = false;

    return isReady;
}

bool canWrite(const string &filePath)
{
    ofstream file(filePath, ios::app);
    bool canWrite;

    canWrite = 0;

    canWrite = file.is_open();
    file.close();

    return canWrite;
}

bool checkMyFile(string filePath, bool isFileOutput)
{

    ifstream testFile(filePath);
    bool checkInput;

    checkInput = false;

    if (testFile.bad())
    {
        cout << "Error, file with path <" << filePath << "> is not exists." << endl;
        testFile.close();
    }
    else if (!isFileText(filePath))
    {
        cout << "Error, filename is not .txt" << endl;
    }
    else if (!isFileOutput && !canRead(filePath))
    {
        cout << "Error, no access to read the file." << endl;
    }
    else if (isFileOutput && !canWrite(filePath))
    {
        cout << "Error, no access to write into the file." << endl;
    }
    // else if (!isFileOutput && !isFileNotEmpty(filePath))
    // {
    //     cout << "Error, file is empty." << endl;
    // }
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

int **createMatrix(int size)
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
    matrix = 0;
}

// int **readMatrixFromFile(int MIN_NUMBER, int MAX_NUMBER, const string &filePath, int &matrixSize)
// {  //переделать

//     const int ERROR_NUMBER = 377070000;
//     const int MIN_LENGTH = 1;
//     const int MAX_LENGTH = 20;
//     // const int MIN_NUMBER = -10000;
//     // const int MAX_NUMBER = 10000;

//     ifstream inputFile(filePath);

//     if (!inputFile.is_open())
//     {
//         cout << "Error opening file." << endl;
//         matrixSize = 0;
//     }

//     if (!(inputFile >> matrixSize))
//     {
//         cout << "Error reading matrix length." << endl;
//         inputFile.close();
//     }

//     if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH)
//     {
//         cout << "Incorrect matrix length, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
//         inputFile.close();
//     }

//     int **matrix = createMatrix(matrixSize);

//     for (int i = 0; i < matrixSize; i++)
//     {
//         for (int j = 0; j < matrixSize; j++)
//         {
//             if (!(inputFile >> matrix[i][j]))
//             {
//                 cout << "Incorrect numeric data: matrix element." << endl;
//                 deleteMatrix(matrix, matrixSize);
//                 inputFile.close();
//             }
//         }
//     }

//     int a;

//     if (!(a += 3))
//             {
//                 cout << "Incorrect numeric data: matrix element." << endl;
//                 deleteMatrix(matrix, matrixSize);
//                 inputFile.close();
//             }

//     inputFile.close();
//     return matrix;
// }

void writeMatrixIntoConsole(int **matrix, int size)
{
    cout << "The result matrix is: " << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

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

    if (inputFile.eof())
    {
        cout << "FILE IS EMPTY" << endl;
        matrix = 0;
    }
    else
    {

        if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH)
        {
            cout << "Incorrect matrix length, the number must fit the range [" << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
            matrix = 0;
        }
        else
        {
            matrix = createMatrix(matrixSize);

            for (i = 0; i < matrixSize; i++)
                for (j = 0; j < matrixSize; j++)
                {
                    // cout << "good: " << inputFile.good() << endl; // fsadfdfaff
                    inputFile >> matrix[i][j];
                }

            if (inputFile.fail())
            {
                cout << "Error with reading matrix data, bad file read." << endl;
                //delete[] matrix;
                deleteMatrix(matrix, matrixSize);
                matrix = 0;
            }
        }
    }

    inputFile.close();
    return matrix;
}

int **readMatrixFromConsole(int &matrixSize)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 20;
    const int MIN_NUMBER = -10000;
    const int MAX_NUMBER = 10000;

    int **matrix;

    matrix = createMatrix(matrixSize);

    matrixSize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write matrix length: ");

    for (int i = 0; i < (matrixSize); i++)
        for (int j = 0; j < matrixSize; j++)
        {
            cout << "Write element [" << i << "," << j << "] of matrix: " << endl;
            matrix[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "");
        }

    return matrix;
}

string askTheFilePath()
{
    string filePath;

    cout << "Write the existing file path: ";
    cin >> filePath;

    return filePath;
}

string assignMyFile(bool isFileOutput)
{
    string filePath;
    bool isIncorrect = true;

    do
    {
        filePath = askTheFilePath();
        isIncorrect = !checkMyFile(filePath, isFileOutput);
    } while (isIncorrect);

    return filePath;
}

// void writeMatrixIntoConsole(int **matrix, int size)
// {
//     cout << "The result matrix is: " << endl;
//     for (int i = 0; i < size; i++)
//     {
//         for (int j = 0; j < size; j++)
//             cout << matrix[i][j] << " ";
//         cout << endl;
//     }
// }

void writeMatrixIntoFile(const string &filePath, int **matrix, int size)
{
    ofstream outputFile(filePath);

    if (!outputFile.is_open())
    {
        cout << "Error creating file." << endl;
        return;
    }

    outputFile << "The result matrix is: " << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            outputFile << matrix[i][j] << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    cout << "Matrix written to file successfully." << endl;
}

int main()
{
    //const int ERROR_NUMBER = 37707;
    const int MIN_NUMBER = -10000;
    const int MAX_NUMBER = 10000;

    bool isFromFile, isToFile, isAllUndone, i;
    int **matrix;
    int matrixSize;
    string filePath;

    isFromFile = false;
    isToFile = false;
    matrixSize = 0;       

    isFromFile = workWithConsoleOrFile(false);

    if (isFromFile)
    {
        isAllUndone = true;
        do
        {
            filePath = assignMyFile(false);
            matrix = readMatrixFromFile(MIN_NUMBER, MAX_NUMBER, filePath, matrixSize);

            if (matrix == 0)
                cout << "Error reading matrix from file. Please try again." << endl;
            else
                isAllUndone = false;

        } while (isAllUndone);
    }
    else
        matrix = readMatrixFromConsole(matrixSize);

    isToFile = workWithConsoleOrFile(true);

    if (isToFile)
    {
        filePath = assignMyFile(true);
        writeMatrixIntoFile(filePath, matrix, matrixSize);
    }
    else
        writeMatrixIntoConsole(matrix, matrixSize);

    deleteMatrix(matrix, matrixSize);
    return 0;
}