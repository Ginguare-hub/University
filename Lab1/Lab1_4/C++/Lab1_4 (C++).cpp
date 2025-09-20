#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    const double MAX_NUMBER = 1024.0;
    const double MIN_NUMBER = -1024.0;
    const int MAX_LENGHT = 10;
    const int MIN_LENGHT = 1;

    int lenght;
    int i;
    double n;
    bool isIncorrect;

    lenght = 0;
    i = 0;
    n = 0.0;
    isIncorrect = false;

    double *a;
    double *b;

    do
    {
        std::cout << "Введите число элементов массива a: ";
        std::cin >> lenght;

        isIncorrect = false;

        if (std::cin.fail())
        {
            isIncorrect = true;
            std::cout << "Ошибка ввода, повторите попытку." << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n')
                ;
        }

        if (!isIncorrect && std::cin.get() != '\n')
        {
            isIncorrect = true;
            std::cout << "Ошибка ввода, повторите попытку." << std::endl;
            while (std::cin.get() != '\n');
        }

        if (!isIncorrect && ((lenght < MIN_LENGHT) || (lenght > MAX_LENGHT)))
        {
            isIncorrect = true;
            std::cout << "Число элементов массива должно лежать в диапазоне [" << MIN_LENGHT << ";" << MAX_LENGHT << "], попробуйте ещё раз." << std::endl;
        }

    } while (isIncorrect);
    
    a = new double[lenght];
    b = new double[lenght];

    for (i = 0; i < lenght; i++)
    {
        do
        {
            std::cout << "Введите N" << i + 1 << " элемент массива: ";
            std::cin >> n;

            isIncorrect = false;

            if (std::cin.fail())
            {
                isIncorrect = true;
                std::cout << "Ошибка ввода, повторите попытку." << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n');
            }

            if (!isIncorrect && std::cin.get() != '\n')
            {
                isIncorrect = true;
                std::cout << "Ошибка ввода, повторите попытку." << std::endl;
                while (std::cin.get() != '\n');
            }

            if (!isIncorrect && ((n < MIN_NUMBER) || (n > MAX_NUMBER)))
            {
                isIncorrect = true;
                std::cout << "Значение элемента массива должно лежать в диапазоне [" << MIN_NUMBER << ";" << MAX_NUMBER << "], попробуйте ещё раз." << std::endl;
            }

        } while (isIncorrect);

        a[i] = n;
    }

    for (i = 0; i < lenght; i++)
    {
        b[i] = 2 * a[i] + i + 1;
        std::cout << "B[" << i << "] = " << b[i] << std::endl;
    }

    return (0);
}