#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    const int MAX = 29;
    const int MIN = 1;

    int n, i, sumOfNumbers, number;
    bool isAllCorrect;

    n = 0;
    i = 0;
    sumOfNumbers = 0;
    number = 1;
    isAllCorrect = true;

    std::cout << "Программа считает сумму заданную в условии задачи №2 варианта №20." << std::endl;

    do
    {
        std::cout << "Введите верхнюю границу суммирования: ";
        std::cin >> n;

        isAllCorrect = true;

        if (std::cin.fail())
        {
            isAllCorrect = false;
            std::cout << "Неправильный ввод, повторите попытку снова." << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n');
        }

        if (isAllCorrect && std::cin.get() != '\n')
        {
            isAllCorrect = false;
            std::cout << "Неправильный ввод, повторите попытку снова." << std::endl;
            while (std::cin.get() != '\n');
        }

        if (isAllCorrect && ((n < MIN) || (n > MAX)))
        {
            isAllCorrect = false;
            std::cout << "Степенью может являться только целое положительное число, которое принадлежит диапазону [" << MIN << ";" << MAX << "]." << std::endl;
        }

    } while (!isAllCorrect);

    for (i = 0; i < n; i++) 
    {
        number = number * -2;
        sumOfNumbers = sumOfNumbers + number;
    }

    std::cout << "Сумма равна " << sumOfNumbers;

    return 0;
}