#include <iostream>
#include <cmath>

using namespace std;

int main()
{

    // setlocale(LC_ALL, "Rus");
    setlocale(LC_ALL, "Russian");

    int checker = 0;
    double a = 1.0;
    double b = 1.0;
    double arithmMean = 1.0;
    double geomMean = 1.0;
    bool isIncorrect = true;
    bool isCycleAllowed = true;

    const int MIN = 0;
    const int MAX = 1000;

    cout << "˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜ a ˜ b, ˜ ˜˜˜˜˜˜˜˜˜˜, ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜." << endl;

    while (isCycleAllowed)
    {
        while (isIncorrect)
        {

            isIncorrect = false;

            cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜ a:  ";
            cin >> a;

            if (cin.fail())
            {
                isIncorrect = true;
                cout << "˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜ ˜˜˜˜˜ a, ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜." << endl;
                cin.clear();
                while (cin.get() != '\n')
                    ;
            }

            if (!isIncorrect && (a < MIN || a > MAX))
            {
                isIncorrect = true;
                cout << "˜˜˜˜˜ a ˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ (" << MIN << ";" << MAX << "), ˜˜˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜." << endl;
            }
        }

        isIncorrect = true;

        while (isIncorrect)
        {
            isIncorrect = false;

            cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜ b:  ";
            cin >> b;

            if (cin.fail())
            {
                isIncorrect = true;
                cout << "˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜ ˜˜˜˜˜ b, ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜." << endl;
                cin.clear();
                while (cin.get() != '\n')
                    ;
            }

            if (!isIncorrect && (b < MIN || b > MAX))
            {
                isIncorrect = true;
                cout << "˜˜˜˜˜ b ˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜ (" << MIN << ";" << MAX << "), ˜˜˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜." << endl;
            }
        }

        isIncorrect = true;

        arithmMean = (a + b) / 2;
        geomMean = sqrt(a * b);

        // cout << arithmMean << endl;
        // cout << geomMean << endl;

        if (arithmMean < geomMean)
        {
            cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜." << endl;
        }
        else
        {
            cout << "˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜." << endl;
        }

        cout << "˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜, ˜˜˜˜˜˜˜ ˜˜˜˜˜ 1, ˜˜˜˜ ˜˜˜, ˜˜ ˜˜˜˜˜ 2" << endl;
        cin >> checker;

        if (checker == 1)
        {
            isCycleAllowed = true;
            cout << endl
                 << "˜˜˜˜˜˜˜ ˜˜˜˜˜˜." << endl;
        }
        else
        {
            isCycleAllowed = false;
        }
    }
    return 0;
}
