//
// Created by regrif07 on 11/7/24.
//

#include <numbers_utility.h>

#include <limits.h>

bool safeIntegerAdd(const int firstOperand, const int secondOperand, int* sum)
{
    if (firstOperand >= 0)
    {
        if (secondOperand > (INT_MAX - firstOperand))
        {
            return false;
        }
    }
    else
    {
        if (secondOperand < (INT_MIN - firstOperand))
        {
            return false;
        }
    }

    *sum = firstOperand + secondOperand;
    return true;
}
