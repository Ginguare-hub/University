#include <iostream>
#include <cmath>

using namespace std;

int main() 
{

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

    while (isAllCorrect) 
    {
    
    cout << "Программа считает среднее арифметическое и среднее геометрическое для чисел a и b, и показывает, что среднее арифметическое этих чисел не меньше их среднего геометрического." << endl;
    
    while (isIncorrect) 
    {
        isIncorrect = false;

        cout << "Введите число a:  ";
        cin >> a;

        if (cin.fail())
        {
            isIncorrect = true;
            cout << "Ошибка в записи числа a, повториет попытку." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }

        if (!isIncorrect && (a < MIN || a > MAX))
        {
            isIncorrect = true;
            cout << "Число a должно быть положительным и лежать в диапазоне (" << MIN << ";" << MAX << "), попробуйте ещё раз." << endl;
        }
    }

    isIncorrect = true;

    while (isIncorrect) 
    {
        isIncorrect = false;

        cout << "Введите число b:  ";
        cin >> b;

        if (cin.fail())
        {
            isIncorrect = true;
            cout << "Ошибка в записи числа b, повториет попытку." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }

        if (!isIncorrect && (b < MIN || b > MAX))
        {
            isIncorrect = true;
            cout << "Число a должно быть положительным и лежать в диапазоне (" << MIN << ";" << MAX << "), попробуйте ещё раз." << endl;
        }
    }

    arithmMean = (a + b) / 2;
    geomMean = sqrt(a * b);

    cout << arithmMean << endl;
    cout << geomMean << endl;

    if (arithmMean < geomMean) 
    {
        cout << "Среднее арифметическое меньше чем среднее геометрическое заданных чисел.";    
    } else 
    {
        cout << "Среднее арифметическое не меньше чем среднее геометрическое заданных чисел.";
    }

    cout << "Если хотите продолжить, введите число 1, если нет, то число 2";

    
    // Try
    //         ReadLn(Checker);
    //         If Checker = 1 Then
    //         Begin
    //             WriteLn('');
    //             WriteLn('Давайте заново');
    //         End
    //         Else
    //             IsAllCorrect := False;
    //     Except
    //         IsAllCorrect := False
    //     End;


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
