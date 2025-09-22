#include <iostream>
#include <cmath>

int main() 
{
    double x0, x1, derivative, lowerLimit, upperLimit, funcFromXEqualX, epsilon;
    int count = 0;

    x0 = 0.0;
    x1 = 0.0;
    derivative = 0.0;
    lowerLimit = 0.0;
    upperLimit = 0.0;

    std::cout << "ѕрограмма находит корень уравнени€ ln(7,622x) Ц 8,59х + 5 = 0 с точностью эпсилон методом простой итерации." << std::endl;
    std::cout << "¬ведите число эпсилон, рекомендуемое значение от 0.1" << std::endl;
    std::cin >> epsilon;

    x1 = (lowerLimit + upperLimit) / 2;
    x0 = x1;

    funcFromXEqualX = ((log(7.622*x0) + 5) / 8.59);
    derivative = 1 / (8.59 * x0);


    return 0;
}