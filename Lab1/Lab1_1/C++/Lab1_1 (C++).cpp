#include <iostream>
#include <cmath>

int main()
{
    setlocale(LC_ALL, "Russian");

    int checker;
    double a;
    double b;
    double arithmMean;
    double geomMean;
    bool isIncorrect;
    bool isCycleAllowed;

    checker = 0;
    a = 0.0;
    b = 0.0;
    arithmMean = 0.0;
    geomMean = 0.0;
    isIncorrect = true;
    isCycleAllowed = true;

    const int MIN = 0;
    const int MAX = 1000;

    std::cout << "Программа считает среднее арифметическое и среднее геометрическое для чисел a и b, и показывает, что среднее арифметическое этих чисел не меньше их среднего геометрического." << std::endl;

    while (isCycleAllowed)
    {
        do
        {

            isIncorrect = false;

            std::cout << "Введите число a: ";
            std::cin >> a;

            if (std::cin.fail())
            {
                isIncorrect = true;
                std::cout << "Ошибка в записи числа a, повториет попытку." << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n');
            }

            if (!isIncorrect && std::cin.get() != '\n') 
            {
                isIncorrect = true;
                std::cout << "Ошибка в записи числа a, повториет попытку." << std::endl;
                while(std::cin.get() != '\n');
            }

            if (!isIncorrect && (a < MIN || a > MAX))
            {
                isIncorrect = true;
                std::cout << "Число a должно быть положительным и лежать в диапазоне [" << MIN << ";" << MAX << "], попробуйте ещё раз." << std::endl;
            }

        } while (isIncorrect);

        isIncorrect = true;

        do
        {
            isIncorrect = false;

            std::cout << "Введите число b: ";
            std::cin >> b;

            if (std::cin.fail())
            {
                isIncorrect = true;
                std::cout << "Ошибка в записи числа b, повториет попытку." << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n');
            }

            if (!isIncorrect && std::cin.get() != '\n') 
            {
                isIncorrect = true;
                std::cout << "Ошибка в записи числа b, повториет попытку." << std::endl;
                while(std::cin.get() != '\n');
            }

            if (!isIncorrect && (b < MIN || b > MAX))
            {
                isIncorrect = true;
                std::cout << "Число b должно быть положительным и лежать в диапазоне [" << MIN << ";" << MAX << "], попробуйте ещё раз." << std::endl;
            }
        } while (isIncorrect);

        isIncorrect = true;

        arithmMean = (a + b) / 2;
        geomMean = sqrt(a * b);

        if (arithmMean < geomMean)
        {
            std::cout << "Среднее арифметическое меньше чем среднее геометрическое заданных чисел." << std::endl;
        }
        else
        {
            std::cout << "Среднее арифметическое не меньше чем среднее геометрическое заданных чисел." << std::endl;
        }

        std::cout << "Если хотите продолжить, введите число 1, если нет, то число 2." << std::endl;
        std::cin >> checker;

        if (checker == 1)
        {
            isCycleAllowed = true;
            std::cout << std::endl << "Давайте заново." << std::endl;
        }
        else
        {
            isCycleAllowed = false;
        }
    }
    return 0;
}
