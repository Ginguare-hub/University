
#include <iostream> 
using namespace std;
int main()
{
    setlocale(LC_ALL, "RU");
    double x, y;
    bool IsCorrect;
    const short min = -32000, max = 32000;
    IsCorrect = true;
    do {
        cout << "Введите значение координаты x равное = ";
        cin >> x;
        if (cin.fail() || std::cin.get() != '\n') 
        {
            cout << "ошибка ввода попробуйте снова\n";
            cin.clear(); 
            while (cin.get() != '\n');
        }
        else { IsCorrect = false; }
    } while (IsCorrect);
    IsCorrect = true;
    do {
        cout << "Введите значение координаты y равное = ";
        cin >> y;
        if (cin.fail() || cin.get() != '\n') {
            cout << "ошибка ввода попробуйте снова\n";
            cin.clear();
            while (cin.get() != '\n');
        }
        else { IsCorrect = false; }
    } while (IsCorrect);

        if ((y < 2 * x) && (y < -2 * x + 4) && (y > 0))
        {
            cout << "Точка M принадлежит замкнутому промежутку D";
        }
        else {
            cout << "Точка M не принадлежит замкнутому промежутку D";
        };
    return 0;
}
