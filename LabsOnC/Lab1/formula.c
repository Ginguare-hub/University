#include "formula.h"

double calculate(int x)
{
    double s;
    s = 0;

    if (x <= T1) 
    {
        s = s + x * R1;
    }
    else
        if (x <= T2)
        {
            s = s + T1 * R1 + (x - T1) * R2;
        }
        else
            s = s + T1 * R1 + (T2 - T1) * R2 + (x - T2) * R3;    

    s = s + F;
    
    return s;
}