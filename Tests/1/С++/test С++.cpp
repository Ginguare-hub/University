#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isFileText(string filePath) {
    const int MIN_PATH_LENGTH = 4;

    string fileExt;
    bool isText;

    fileExt = "";
    isText = true;

    if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.find(".txt") == string::npos))
        isText = false;

    return isText;
}

bool canRead(string filePath) {
    bool isReady;
    ifstream testFile;

    isReady = false;
    testFile.open(filePath);

    if (testFile.is_open()) {
        testFile.close();
        isReady = true;
    }

    testFile.close();
    return isReady;
}

bool canWrite(const string& filePath) {
    ofstream outputFile;
    bool canWrite;

    canWrite = false;

    outputFile.open(filePath, ios::app);
    canWrite = outputFile.is_open();
    outputFile.close();

    outputFile.close();
    return canWrite;
}

bool checkMyFile(string filePath, bool isFileOutput) {
    ifstream testFile;
    bool checkInput;

    checkInput = false;
    testFile.open(filePath);

    if (testFile.fail()) {
        cout << "Error, file with path <" << filePath << "> is not exists or cannot be read." << endl;
        testFile.close();
    }
    else if (!isFileText(filePath)) {
        cout << "Error, filename is not .txt" << endl;
    }
    else if (!isFileOutput && !canRead(filePath)) {
        cout << "Error, no access to read the file." << endl;
    }
    else if (isFileOutput && !canWrite(filePath)) {
        cout << "Error, no access to write into the file." << endl;
    }
    else {
        checkInput = true;
        cout << "Assigning is completed successfully." << endl;
    }

    testFile.close();
    return checkInput;
}

int sumHourglassPositive(int** arr, int n) {
    int s;
    int l;
    int r;
    int a;
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
        a = l++;
        for (int j = a; j < r ; j++) {
            if (arr[i][j] > 0) {
                s = s + arr[i][j];
            }
        }
    }
    return s;
}

int inputOutputConsole() {
    int n;
    bool isInputCorrect;
    int resultValue;
    int** arr;
    do {
        isInputCorrect = false;
        cout << "Enter the array size: " << endl;
        if (!(cin >> n)) {
            isInputCorrect = true;
            cout << "Enter a valid integer." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if (n < 1) {
            isInputCorrect = true;
            cout << "Enter a number greater than 0." << endl;
        }
    } while (isInputCorrect);

    arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            do {
                cout << "Number " << i++ << "-" << j++ << endl;
                isInputCorrect = false;
                if (!(cin >> arr[i][j])) {
                    isInputCorrect = true;
                    cout << "Enter a valid integer." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
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

int inputOutputData(const string& Path) {
    ifstream f(Path);
    int n;
    int** arr;
    int resultValue;

    f >> n;
    arr = new int* [n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f >> arr[i][j];
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

    return resultValue;
}

string pathInput() {
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

string pathOutput() {
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


void outputData(int resultValue, const string& outPath) {
    ofstream f(outPath);
    f << resultValue << endl;
    f.close();
}

void inputSelection() {
    int resultValue;
    int input;
    bool isInputIncorrect;

    do {
        isInputIncorrect = true;
        cout << "How will you display the answer ?" << endl;
        cout << "0.Console                 1.Files" << endl;

        cin >> input;

        if (cin.fail())
        {
            isInputIncorrect = true;
            cout << "Error: enter an integer" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        if (cin.get() != '\n')
        {
            isInputIncorrect = true;
            cout << "Error: Input contains extra characters." << endl;
            while (cin.get() != '\n');
        }
        if (input < 0 || input > 1)
        {
            isInputIncorrect = true;
            cout << "Enter the number 0 or 1" << endl;
        }

        else
        {
            if (input == 0)
                resultValue = inputOutputConsole();
            else
            {
                resultValue = inputOutputData(pathInput());
            }
        }
    } while (isInputIncorrect);
}

void outputSelection(int resultValue) {

    int output;
    bool isInputIncorrect;
    string outPath;
 
    do{
        isInputIncorrect = true;
        cout << "How will you display the answer ?" << endl;
        cout << "0.Console                 1.Files" << endl;
        
        cin >> output;

        if (cin.fail())
        {
            isInputIncorrect = true;
            cout << "Error: enter an integer" << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
        if (cin.get() != '\n')
        {
            isInputIncorrect = true;
            cout << "Error: Input contains extra characters." << endl;
            while (cin.get() != '\n');
        }
        if (output < 0 || output > 1)
        {
            isInputIncorrect = true;
            cout << "Enter the number 0 or 1" << endl;
        }

        else
        {
            if (output == 0)
                cout << resultValue << endl;
            else
            {
                outPath = pathOutput();
                outputData(resultValue, outPath);
                cout << "Result written to: " + outPath << endl;
            }
        }
    }while (isInputIncorrect);
}

int main() {
    int finalResult;
    inputSelection();
    outputSelection;
    return 0;
}
