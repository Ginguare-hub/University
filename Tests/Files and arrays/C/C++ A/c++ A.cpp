#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//const int ERROR_NUMBER = 37707;
const int MIN_LENGTH = 1;
const int MAX_LENGTH = 20;
const int MIN_NUMBER = -10000;
const int MAX_NUMBER = 10000;

// Проверки ----------------------------------------------------------------------

int readAndVerify(int MIN_NUMBER, int MAX_NUMBER, const string& message) {
    int number = 0;
    bool isCorrect = false;
    
    do {
        cout << message;
        cin >> number;
        
        if (cin.fail()) {
            cout << "Incorrect input, try again." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            isCorrect = false;
        } else if (number < MIN_NUMBER || number > MAX_NUMBER) {
            cout << "The number must fit the range [" << MIN_NUMBER << "," << MAX_NUMBER << "]." << endl;
            isCorrect = false;
        } else {
            isCorrect = true;
        }
    } while (!isCorrect);
    
    return number;
}

bool isFileText(const string& filePath) {

    const int MIN_PATH_LENGTH = 4;

    string fileExt;
    bool isText;

    isText = true;

    if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.find(".txt") == string::npos))
        isText = false;

    return isText;
}

bool isFileNotEmpty(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }
    
    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();
    file.close();
    
    return fileSize > 0;
}

bool canRead(const string& filePath) {
    ifstream file(filePath);
    bool canRead = file.is_open();
    file.close();
    return canRead;
}

bool canWrite(const string& filePath) {
    ofstream file(filePath, ios::app);
    bool canWrite = file.is_open();
    file.close();
    return canWrite;
}

bool checkMyFile(const string& filePath, bool isFileOutput) {
    
    ifstream testExist(filePath);
    if (!testExist.is_open()) {
        cout << "Error, file with path <" << filePath << "> is not exists." << endl;
        return false;
    }
    testExist.close();
    
    if (!isFileText(filePath)) {
        cout << "Error, filename is not .txt" << endl;
        return false;
    }
    
    if (!isFileOutput && !canRead(filePath)) {
        cout << "Error, no access to read the file." << endl;
        return false;
    }
    
    if (isFileOutput && !canWrite(filePath)) {
        cout << "Error, no access to write into the file." << endl;
        return false;
    }
    
    if (!isFileOutput && !isFileNotEmpty(filePath)) {
        cout << "Error, file is empty." << endl;
        return false;
    }
    
    cout << "Assigning is completed successfully." << endl;
    return true;
}

// Проверки ----------------------------------------------------------------------

bool workWithConsoleOrFile(bool isOutput) {
    int number = 0;
    
    if (isOutput) {
        cout << "If data is output to the console write 0, if from file write 1." << endl;
    } else {
        cout << "If data is entered from the console write 0, if from file write 1." << endl;
    }
    
    number = readAndVerify(0, 1, "> ");
    bool isFromFile = (number == 1);
    
    if (isFromFile) {
        if (isOutput) {
            cout << "The data is output to a file." << endl;
        } else {
            cout << "The data is entered from a file." << endl;
        }
    } else {
        if (isOutput) {
            cout << "The data is output to the console." << endl;
        } else {
            cout << "The data is entered from the console." << endl;
        }
    }
    
    return isFromFile;
}

int** createMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    return matrix;
}

void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** readMatrixFromFile(int MIN_NUMBER, int MAX_NUMBER, const string& filePath, int& matrixSize) {
    ifstream inputFile(filePath);
    
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        matrixSize = 0;
        return nullptr;
    }
    
    if (!(inputFile >> matrixSize)) {
        cout << "Error reading matrix length." << endl;
        inputFile.close();
        return nullptr;
    }
    
    if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH) {
        cout << "Incorrect matrix length, the number must fit the range [" 
             << MIN_LENGTH << "," << MAX_LENGTH << "]." << endl;
        inputFile.close();
        return nullptr;
    }
    
    int** matrix = createMatrix(matrixSize);
    
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            if (!(inputFile >> matrix[i][j])) {
                cout << "Incorrect numeric data: matrix element." << endl;
                deleteMatrix(matrix, matrixSize);
                inputFile.close();
                return nullptr;
            }
        }
    }
    
    inputFile.close();
    return matrix;
}

int** readMatrixFromConsole(int& matrixSize) {
    matrixSize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write matrix length: ");
    
    int** matrix = createMatrix(matrixSize);
    
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            string prompt = "Write element [" + to_string(i) + "," + to_string(j) + "] of matrix: ";
            matrix[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, prompt);
        }
    }
    
    return matrix;
}

string askTheFilePath() {
    string filePath;
    cout << "Write the existing file path: ";
    cin >> filePath;
    return filePath;
}

string assignMyFile(bool isFileOutput) {
    string filePath;
    bool isCorrect = false;
    
    do {
        filePath = askTheFilePath();
        isCorrect = checkMyFile(filePath, isFileOutput);
    } while (!isCorrect);
    
    return filePath;
}

void writeMatrixIntoConsole(int** matrix, int size) {
    cout << "The result matrix is: " << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void writeMatrixIntoFile(const string& filePath, int** matrix, int size) {
    ofstream outputFile(filePath);
    
    if (!outputFile.is_open()) {
        cout << "Error creating file." << endl;
        return;
    }
    
    outputFile << "The result matrix is: " << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            outputFile << matrix[i][j] << " ";
        }
        outputFile << endl;
    }
    
    outputFile.close();
    cout << "Matrix written to file successfully." << endl;
}

int main() {
    bool isFromFile = false;
    bool isToFile = false;
    int** matrix = nullptr;
    int matrixSize = 0;
    
    // Ввод данных
    isFromFile = workWithConsoleOrFile(false);
    
    if (isFromFile) {
        bool isAllDone = false;
        
        do {
            string filePath = assignMyFile(false);
            matrix = readMatrixFromFile(MIN_NUMBER, MAX_NUMBER, filePath, matrixSize);
            
            if (matrix != nullptr) {
                isAllDone = true;
            } else {
                cout << "Error reading matrix from file. Please try again." << endl;
            }
        } while (!isAllDone);
        
    } else {
        matrix = readMatrixFromConsole(matrixSize);
    }
    
    // Вывод данных
    isToFile = workWithConsoleOrFile(true);
    
    if (isToFile) {
        string filePath = assignMyFile(true);
        writeMatrixIntoFile(filePath, matrix, matrixSize);
    } else {
        writeMatrixIntoConsole(matrix, matrixSize);
    }
    
    delete matrix;
    
    return 0;
}