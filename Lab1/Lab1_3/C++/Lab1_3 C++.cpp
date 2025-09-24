#include <iostream>
#include <cmath>

int main() 
{
    setlocale(LC_ALL, "Russian");

    const double a = 7.622;
    const double b = 8.59;
    const double c = 5.0;

    double x0, x1, derivative, lowerLimit, upperLimit, equivEquation, epsilon;
    int count = 0;
    bool isIncorrect = false;

    x0 = 0.0;
    x1 = 0.0;
    derivative = 0.0;
    lowerLimit = 1.0;
    upperLimit = 0.5;

    std::cout << "Программа находит корень уравнения ln(" << a << "x) - " << b << "х + " << c << " = 0 с точностью эпсилон методом простой итерации." << std::endl;

    do
    {
        std::cout << "Введите число эпсилон, рекомендуемое значение от 0.1" << std::endl;
        std::cin >> epsilon;

        isIncorrect = false;

        if (std::cin.fail())
        {
            isIncorrect = true;
            std::cout << "Неправильный ввод, повторите попытку снова." << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
        }

        if (!isIncorrect && std::cin.get() != '\n')
        {
            isIncorrect = true;
            std::cout << "Неправильный ввод, повторите попытку снова." << std::endl;
            while (std::cin.get() != '\n');
        }

        if (!isIncorrect && ((epsilon < 0.0) || (epsilon = 0)))
        {
            isIncorrect = true;
            std::cout << "Эпсилон - положительное сколь угодно малое вещественное число, эпсилон должен быть больше 0" << std::endl;
        }

    } while (isIncorrect);

    x1 = (lowerLimit + upperLimit) / 2;
    x0 = x1;

    equivEquation = ((log(a * x0) + c) / b);
    derivative = 1 / (c * x0);

    if (abs(derivative)  < 1)
    {
        do
        {
            count = count + 1;
            x0 = x1;
            equivEquation = (log(a * x0) + c) / b;
            x1 = equivEquation;
        } while (((abs(x1 - x0)) > epsilon) && (count < 100));

        std::cout << "X = " << x1 << " " << count << std::endl;  
    } 
    else
    {
        std::cout << "Корней методом простой итерации на данном промежутке найти не удалось" << std::endl; 
    } 

    return 0;
}