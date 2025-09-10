#include <iostream>
#include <cmath>

using namespace std;

int main() {

    setlocale(LC_ALL, "Rus");

    int checker = 0;
    double a = 1.0;
    double b = 1.0;
    double arithmMean = 1.0;
    double geomMean = 1.0;
    bool isIncorrect = true;
    bool isAllCorrect = true;
    
    const int MIN = 0;
    const int MAX = 1000;

    while (isAllCorrect) {
    
    cout << "Программа считает среднее арифметическое и среднее геометрическое для чисел A и B, и показывает, что среднее арифметическое этих чисел не меньше их среднего геометрического." << endl;
    
    cout << "Введите число a:  ";
    cin >> a;
    cout << "Введите число b:  ";
    cin >> b;

    arithmMean = (a + b) / 2;
    geomMean = sqrt(a * b);



    cout << arithmMean << endl;
    cout << geomMean << endl;

    if (arithmMean < geomMean) {
        cout << "Среднее арифметическое меньше чем среднее геометрическое заданных чисел.";    
    } else {
        cout << "Среднее арифметическое не меньше чем среднее геометрическое заданных чисел.";
    }

    isAllCorrect = false;

    }
    return 0;
}

// #include <iostream>
// #include <vector>
// #include <string>

// using namespace std;

// int main()
// {
//     vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

//     for (const string& word : msg)
//     {
//         cout << word << " ";
//     }
//     cout << endl;
// }
