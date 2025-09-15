#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");

    int lenght;
    int i;
    double n;
    bool isAllCorrect;

    const double MAX_NUMBER = 1024.0;
    const double MIN_NUMBER = -1024.0;
    const double MAX_LENGHT = 10;
    const double MIN_LENGHT = 1;

    lenght = 1.0;
    i = 0;
    n = 1.0;
    isAllCorrect = true;

    {new double a[lenght]};
    {new double b[lenght]};

    do
    {
        std::cout << "Введите число элементов массива a: ";
        std::cin >> lenght;

        isAllCorrect = true;

        if (std::cin.fail())
        {
            isAllCorrect = false;
            std::cout << "Ошибка ввода, повторите попытку." << std::endl;
            std::cin.clear();
            while (std::cin.get() != '\n')
                ;
        }

        if (isAllCorrect && std::cin.get() != '\n')
        {
            isAllCorrect = false;
            std::cout << "Ошибка ввода, повторите попытку." << std::endl;
            while (std::cin.get() != '\n')
                ;
        }

        if (isAllCorrect && ((lenght < MIN_LENGHT) || (lenght > MAX_LENGHT)))
        {
            isAllCorrect = false;
            std::cout << "Число элементов массива должно лежать в диапазоне [" << MIN_LENGHT << ";" << MAX_LENGHT << "], попробуйте ещё раз." << std::endl;
        }

    } while (!isAllCorrect);

    // std::array<double, lenght> a;
    // std::array<double, lenght> b;

    for (i = 0; i < lenght; i++)
    {
        do
        {
            std::cout << "Введите N" << i + 1 << " элемент массива: ";
            std::cin >> n;

            isAllCorrect = true;

            if (std::cin.fail())
            {
                isAllCorrect = false;
                std::cout << "Ошибка ввода, повторите попытку." << std::endl;
                std::cin.clear();
                while (std::cin.get() != '\n')
                    ;
            }

            if (isAllCorrect && std::cin.get() != '\n')
            {
                isAllCorrect = false;
                std::cout << "Ошибка ввода, повторите попытку." << std::endl;
                while (std::cin.get() != '\n')
                    ;
            }

            if (isAllCorrect && ((n < MIN_NUMBER) || (n > MAX_NUMBER)))
            {
                isAllCorrect = false;
                std::cout << "Значение элемента массива должно лежать в диапазоне [" << MIN_NUMBER << ";" << MAX_NUMBER << "], попробуйте ещё раз." << std::endl;
            }

        } while (!isAllCorrect);
    }

    for (i = 0; i < lenght; i++)
    {
        b[i] = 2 * a[i] + i + 1;
    }

    for (i = 0; i < lenght; i++)
    {
        std::cout << "B[" << i << "] = " << b[i] << std::endl;
    }

    return (0);
}