#include <iostream>
#include <cmath>

int main() 
{
    setlocale(LC_ALL, "Russian");

    const double A = 7.622;
    const double B = 8.59;
    const double C = 5.0;
    const double UPPER_LIMIT = 0.5;
    const double LOWER_LIMIT = 1.0;
    const int MAX_ITERATIONS = 20;
    const int NUMB_PRECISION = 15;


    double x0, x1, derivative, equivEquation, epsilon, diff;
    int count = 0;
    bool isIncorrect = false;

    x0 = 0.0;
    x1 = 0.0;
    derivative = 0.0;
    equivEquation = 0.0;
    epsilon = 1;
    diff = 0.0;

    std::cout << "Программа находит корень уравнения ln(" << A << "x) - " << B << "х + " << C << " = 0 с точностью эпсилон методом простой итерации." << std::endl;

    do
    {
        std::cout << "Введите положительное число эпсилон, рекомендуемое значение менее 0.1" << std::endl;
        std::cin >> epsilon;

        isIncorrect = false;

        if (std::cin.fail() || std::cin.get() != '\n')
        {
            isIncorrect = true;
            std::cout << "Неправильный ввод, повторите попытку снова." << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
        }

        // if (!isIncorrect && std::cin.get() != '\n')
        // {
        //     isIncorrect = true;
        //     std::cout << "Неправильный ввод, повторите попытку снова." << std::endl;
        //     while (std::cin.get() != '\n');
        // }

        if (!isIncorrect && ((epsilon < 0.0) || (epsilon == 0)))
        {
            isIncorrect = true;
            std::cout << "Эпсилон - положительное сколь угодно малое вещественное число, эпсилон должен быть больше 0" << std::endl;
        }

    } while (isIncorrect);

    x1 = (LOWER_LIMIT + UPPER_LIMIT) / 2;
    x0 = x1;

    equivEquation = ((log(A * x0) + C) / B);
    derivative = 1 / (C * x0);

    if (abs(derivative)  < 1)
    {
        do
        {
            count = count + 1;
            x0 = x1;
            equivEquation = (log(A * x0) + C) / B;
            x1 = equivEquation;
            diff = abs(x1 - x0);
        } while ((diff > epsilon) && (count < MAX_ITERATIONS));

        std::cout.precision(15);
        std::cout << "X = " << x1 << " " << count << std::endl; 
    } 
    else
    {
        std::cout << "Корней методом простой итерации на данном промежутке найти не удалось" << std::endl; 
    } 

    return 0;
}