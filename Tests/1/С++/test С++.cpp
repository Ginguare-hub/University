#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isFileText(string filePath) 
{
    const int MIN_PATH_LENGTH = 4;

    string fileExt;
    bool isText;

    fileExt = "";
    isText = true;

    if ((filePath.length() < MIN_PATH_LENGTH) ||
        (filePath[filePath.length() - 1] != 't') ||
        (filePath[filePath.length() - 2] != 'x') ||
        (filePath[filePath.length() - 3] != 't') ||
        (filePath[filePath.length() - 4] != '.'))
    {
        isText = false;
    }
    return isText;
}

bool canRead(string filePath) 
{
    bool isReady;
    ifstream testFile;

    isReady = false;
    testFile.open(filePath);

    if (testFile.is_open()) {
        testFile.close();
        isReady = true;
    }
    return isReady;
}

bool canWrite(const string& filePath) 
{
    ofstream outputFile;
    bool canWrite;

    canWrite = false;

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

    if (testFile.fail()) {
        cout << "Error, file with path <" << filePath << "> is not exists or cannot be read." << endl;
    }
    else 
        if (!isFileText(filePath)) {
        cout << "Error, filename is not .txt" << endl;
    }
    else 
        if (!isFileOutput && !canRead(filePath)) {
        cout << "Error, no access to read the file." << endl;
    }
    else 
        if (isFileOutput && !canWrite(filePath)) {
        cout << "Error, no access to write into the file." << endl;
    }
    else {
        checkInput = true;
        cout << "Assigning is completed successfully." << endl;
    }
    testFile.close();
    return checkInput;
}

int sumHourglassPositive(int** arr, int n) 
{
    int s, l, r, a;
    s = 0;
    for (int i = 0; i < n; i++) {
        if (i < (n - 1 - i)) {
            l = i;
            r = n - 1 - i;
        }
        else {
            l = n - 1 - i;
            r = i;
        }
        
        for (int j = l + 1; j < r; j++) {
            if (arr[i][j] > 0) {
                s = s + arr[i][j];
            }
        }
    }
    return s;
}

int inputOutputConsole() 
{
    int n;
    bool isInputCorrect;
    int resultValue;
    int** arr;

    do {
        isInputCorrect = false;
        cout << "Enter the array size: " << endl;
        if (!(cin >> n)) {
            cout << "Enter a valid integer." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            isInputCorrect = true;
        }
        else if (n < 1 || n > 1000) {
            cout << "Enter a number between 1 and 1000." << endl;
            isInputCorrect = true;
        }
    } while (isInputCorrect);

    arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            do {
                cout << "Number " << i + 1 << "-" << j + 1 << ": ";
                isInputCorrect = false;
                if (!(cin >> arr[i][j])) {
                    cout << "Enter a valid integer." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    isInputCorrect = true;
                }
            } while (isInputCorrect);
        }
    }

    resultValue = sumHourglassPositive(arr, n);

    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    return resultValue;
}


int inputOutputData(const string& Path, bool& taskSuccess)
{
    ifstream f(Path);
    int n;
    int** arr;
    int resultValue;

    taskSuccess = false;

    if (!(f >> n)) {
        cout << "Error: failed to read matrix size." << endl;
        f.close();
        return 0;
    }

    arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(f >> arr[i][j])) {
                cout << "Error: failed to read element " << i + 1 << "-" << j + 1 << endl;
                for (int k = 0; k <= i; ++k) delete[] arr[k];
                delete[] arr;
                f.close();
                return 0;
            }
        }
    }
    f.close();

    cout << "Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    resultValue = sumHourglassPositive(arr, n);

    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;

    taskSuccess = true;
    return resultValue;
}

string pathInput() 
{
    string p;
    bool performance;
    cout << "Enter the path to the input file: ";
    do {
        cin >> p;
        performance = checkMyFile(p, false);
        performance = !performance;
    } while (performance);
    return p;
}

string pathOutput() 
{
    string p;
    bool performance;
    cout << "Enter the path to the output file: ";
    do {
        cin >> p;
        performance = checkMyFile(p, true);
        performance = !performance;
    } while (performance);
    return p;
}


void outputData(int resultValue, const string& outPath) 
{
    ofstream f(outPath);
    f << resultValue << endl;
    f.close();
}

int inputSelection() 
{
    int resultValue;
    int input;
    bool isInputIncorrect;
    bool taskSuccess;
    bool hasError;
    do {
        isInputIncorrect = true;
        cout << "How do you want to enter the data?" << endl;
        cout << "0.Console                 1.Files" << endl;

        cin >> input;

        if (cin.fail()) {
            isInputIncorrect = true;
            cout << "Error: enter an integer" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        if (cin.get() != '\n') {
            isInputIncorrect = true;
            cout << "Error: Input contains extra characters." << endl;
            while (cin.get() != '\n');
        }
        if (input < 0 || input > 1) {
            isInputIncorrect = true;
            cout << "Enter the number 0 or 1" << endl;
        }
        else {
            if (input == 0)
                resultValue = inputOutputConsole();
            else {
                hasError = true;  
                do {
                    string path = pathInput();
                    resultValue = inputOutputData(path, taskSuccess);
                    hasError = !taskSuccess; 
                } while (hasError);
            }

            isInputIncorrect = false;
        }

    } while (isInputIncorrect);

    return resultValue;
}


void outputSelection(int resultValue) 
{
    int output;
    bool isInputIncorrect;
    string outPath;

    do {
        isInputIncorrect = true;
        cout << "How will you display the answer ?" << endl;
        cout << "0.Console                 1.Files" << endl;

        cin >> output;

        if (cin.fail()) {
            isInputIncorrect = true;
            cout << "Error: enter an integer" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        if (cin.get() != '\n') {
            isInputIncorrect = true;
            cout << "Error: Input contains extra characters." << endl;
            while (cin.get() != '\n');
        }
        if (output < 0 || output > 1) {
            isInputIncorrect = true;
            cout << "Enter the number 0 or 1" << endl;
        }
        else {
            if (output == 0)
                cout << resultValue << endl;
            else {
                outPath = pathOutput();
                outputData(resultValue, outPath);
                cout << "Result written to: " + outPath << endl;
            }
            isInputIncorrect = false;
        }
    } while (isInputIncorrect);
}


int main() 
{
    int resultValue = inputSelection();
    outputSelection(resultValue); 
    return 0; 
}
