#include <iostream>
#include <cassert>

using namespace std;

// int intAdd(int a, int b)
// {
//     return a + b;
// }

// void testAdd()
// {
//     assert(intAdd(2, 3) == 5);
//     assert(intAdd(0, 0) == 1);
//     assert(intAdd(-2, 3) == 1);
// }

// int main()
// {
//     testAdd();
//     return 0;
// }

bool trnglTest(int x1, int x2, int x3, int y1, int y2, int y3)
{
    // int* arrayOfCoords;
    // int i, numberOfCoords;
    double l1, l2, l3;
    bool isRight;

    x1, x2, x3, y1, y2, y3 = 0;
    isRight = true;

    // cin >> x1, y1;
    // cin >> x2, y2;
    // cin >> x3, y3;

    l1 = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    l2 = sqrt((x2 - x3)*(x2 - x3) + (y2 - y3)*(y2 - y3));
    l3 = sqrt((x3 - x1)*(x3 - x1) + (y3 - y1)*(y3 - y1));

    if ((l1 + l2 > l3) && (l2 + l3 > l1) && (l1 + l3 > l2))
        cout << "Is rigth.\n";
    else 
    {
        cout << "Is wrong.\n";
        isRight = false;
    }
    return isRight;
}

void testTrnlTest()
{
    assert(trnglTest(2,3, 4,5, 8,8) == true);
    assert(trnglTest(0,0, 1,0, 2,0) == false);
   // assert(intAdd(-2, 3) == 1);
}

int main()
{
    testTrnlTest();
    return 0;
}