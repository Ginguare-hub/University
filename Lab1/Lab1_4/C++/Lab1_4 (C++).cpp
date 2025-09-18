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
    bool isAllCorrect;

    lenght = 0;
    i = 0;
    n = 0.0;
    isAllCorrect = true;

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
            while (std::cin.get() != '\n');
        }

        if (isAllCorrect && ((lenght < MIN_LENGHT) || (lenght > MAX_LENGHT)))
        {
            isAllCorrect = false;
            std::cout << "Число элементов массива должно лежать в диапазоне [" << MIN_LENGHT << ";" << MAX_LENGHT << "], попробуйте ещё раз." << std::endl;
        }

    } while (!isAllCorrect);
    
    double *a = new double[lenght];
    double *b = new double[lenght];

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
                while (std::cin.get() != '\n');
            }

            if (isAllCorrect && std::cin.get() != '\n')
            {
                isAllCorrect = false;
                std::cout << "Ошибка ввода, повторите попытку." << std::endl;
                while (std::cin.get() != '\n');
            }

            if (isAllCorrect && ((n < MIN_NUMBER) || (n > MAX_NUMBER)))
            {
                isAllCorrect = false;
                std::cout << "Значение элемента массива должно лежать в диапазоне [" << MIN_NUMBER << ";" << MAX_NUMBER << "], попробуйте ещё раз." << std::endl;
            }

        } while (!isAllCorrect);

        a[i] = n;
        
    }


    for (i = 0; i < lenght; i++)
    {
        b[i] = 2 * a[i] + i + 1;
        std::cout << "B[" << i << "] = " << b[i] << std::endl;
    }

    // for (i = 0; i < lenght; i++)
    // {
    //     std::cout << "B[" << i << "] = " << b[i] << std::endl;
    // }

    return (0);
}