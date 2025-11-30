#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writePurpose() 
{
    cout << "A two-dimensional matrix A of order n is given. The program arranges the elements of the rows with even matrix numbers in descending order." << endl;
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

    return isReady;
}

bool canWrite(const string &filePath)
{
    ofstream outputFile;
    bool canWrite;
    
    canWrite = 0;
    
    outputFile.open(filePath, ios::app);
    canWrite = outputFile.is_open();
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
    else if (!isFileText(filePath))
        cout << "Error, filename is not .txt" << endl;
    else if (!isFileOutput && !canRead(filePath))
        cout << "Error, no access to read the file." << endl;
    else if (isFileOutput && !canWrite(filePath))
        cout << "Error, no access to write into the file." << endl;
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
    const int MAX_LENGTH = 30;

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
                //cout << "Error with reading matrix data, bad file read." << endl;
                //delete[] matrix;
                deleteMatrix(matrix, matrixSize);
                matrix = 0;
            }
        }
    }

    inputFile.close();
    return matrix;
}

int **readMatrixFromConsole(const int MIN_NUMBER, const int MAX_NUMBER, int &matrixSize)
{
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 30;

    int **matrix;
    int i, j;

    i, j = 0;

    
    matrixSize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write matrix length: ");

    matrix = createMatrix(matrixSize);

    for (i = 0; i < matrixSize; i++)
        for (j = 0; j < matrixSize; j++)
        {
            cout << "Write element [" << i << "," << j << "] of matrix: ";
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
    bool isIncorrect;
    
    isIncorrect = false;               //fdfafadsfdasff

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

void writeMatrixIntoFile(string &filePath, int **matrix, int size)
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

void readingStage(int **&matrix, int &matrixSize) 
{
    const int MIN_NUMBER = -10000;
    const int MAX_NUMBER = 10000;

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
            matrix = readMatrixFromFile(MIN_NUMBER, MAX_NUMBER, filePath, matrixSize);

            if (matrix == 0)
                cout << "Error with reading matrix data, bad file read." << endl;
            else
                isAllUndone = false;

        } while (isAllUndone);
    }
    else
        matrix = readMatrixFromConsole(MIN_NUMBER, MAX_NUMBER, matrixSize);
}

void writingStage(int **matrix, int matrixSize)
{
    bool isAllUndone, isOutput, isToFile;
    string filePath;

    isToFile = workWithConsoleOrFile(true);
    isOutput = true;

    if (isToFile)
    {
        filePath = assignMyFile(isOutput);
        writeMatrixIntoFile(filePath, matrix, matrixSize);
    }
    else
        writeMatrixIntoConsole(matrix, matrixSize);
}

int main()
{

    //bool isToFile;
    int **matrix;
    int matrixSize;
    //string filePath;

    //isFromFile = false;
    //isToFile = false;
    //isOutput = false;
    //isAllUndone = true;
    
    matrix = nullptr;
    matrixSize = 0;  
    
    writePurpose();
    readingStage(matrix, matrixSize);
    writingStage(matrix, matrixSize);

    // isFromFile = workWithConsoleOrFile(false);
    // isOutput = false;

    // if (isFromFile)
    // {
    //     isAllUndone = true;
    //     do
    //     {
    //         filePath = assignMyFile(isOutput);
    //         matrix = readMatrixFromFile(MIN_NUMBER, MAX_NUMBER, filePath, matrixSize);

    //         if (matrix == 0)
    //             cout << "Error with reading matrix data, bad file read." << endl;
    //         else
    //             isAllUndone = false;

    //     } while (isAllUndone);
    // }
    // else
    //     matrix = readMatrixFromConsole(MIN_NUMBER, MAX_NUMBER, matrixSize);

    // isToFile = workWithConsoleOrFile(true);
    // isOutput = true;

    // if (isToFile)
    // {
    //     filePath = assignMyFile(isOutput);
    //     writeMatrixIntoFile(filePath, matrix, matrixSize);
    // }
    // else
    //     writeMatrixIntoConsole(matrix, matrixSize);

    deleteMatrix(matrix, matrixSize);
    return 0;
}