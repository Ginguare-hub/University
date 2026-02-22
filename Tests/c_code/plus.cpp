#include <iostream>
#include <iomanip>

int main()
{
    double a = 0.2;
    double b = 0.1;
    std::cout << std::fixed << std::setprecision(20) 
    << (a + b);
    return 0;
}