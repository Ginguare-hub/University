#include <iostream>

void get(int i);

void get(int *i)
{
    std::cout << "Pointer\n";
}

int main()
{
    int *i;

    i = NULL;

    get(i);

    i = nullptr;

    get(i);

    std::cout << "\n=============\n";

    get(NULL);
    get(nullptr);
    return 0;
}

void get(int i)
{
    std::cout << "Number\n";
}