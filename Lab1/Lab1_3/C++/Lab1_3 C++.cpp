#include <iostream>
#include <cmath>

int main() 
{
    setlocale(LC_ALL, "Russian");

    double x0, x1, derivative, lowerLimit, upperLimit, funcFromXEqualX, epsilon;
    int count = 0;

    x0 = 0.0;
    x1 = 0.0;
    derivative = 0.0;
    lowerLimit = 0.0;
    upperLimit = 1.0;

    std::cout << "Программа находит корень уравнения ln(7,622x) – 8,59х + 5 = 0 с точностью эпсилон методом простой итерации." << std::endl;
    std::cout << "Введите число эпсилон, рекомендуемое значение от 0.1" << std::endl;
    std::cin >> epsilon;

    x1 = (lowerLimit + upperLimit) / 2;
    x0 = x1;

    funcFromXEqualX = ((log(7.622*x0) + 5) / 8.59);
    derivative = 1 / (8.59 * x0);

    if (abs(derivative)  < 1)
    {
        do
        {
            count = count + 1;
            x0 = x1;
            funcFromXEqualX = (log(7.622 * x0) + 5) / 8.59;
            x1 = funcFromXEqualX;
        } while (((abs(x1 - x0)) > epsilon) && (count < 100));

        std::cout << "X = " << x1 << " " << count << std::endl;  
    } 
    else
    {
        std::cout << "Корней методом простой итерации на данном промежутке найти не удалось" << std::endl; 
    } 


    return 0;
}