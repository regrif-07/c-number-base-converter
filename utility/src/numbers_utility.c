//
// Created by regrif07 on 11/7/24.
//

#include <numbers_utility.h>

#include <limits.h>

bool safeLongLongAdd(const long long firstOperand, const long long secondOperand, long long* out)
{
    if (firstOperand >= 0)
    {
        if (secondOperand > (LLONG_MAX - firstOperand))
        {
            return false;
        }
    }
    else
    {
        if (secondOperand < (LLONG_MIN - firstOperand))
        {
            return false;
        }
    }

    *out = firstOperand + secondOperand;
    return true;
}

bool safeLongLongMultiply(const long long firstOperand, const long long secondOperand, long long* out)
{
    const long long result = firstOperand * secondOperand;
    if (firstOperand != 0 && result / firstOperand != secondOperand)
    {
        return false;
    }

    *out = result;
    return true;
}

bool safeLongLongPow(const long long base, const unsigned long long exponent, long long* out)
{
    if (exponent == 0)
    {
        *out = 1;
        return true;
    }

    long long result = base;
    for (int i = 1; i < exponent; ++i)
    {
        if (!safeLongLongMultiply(result, base, &result))
        {
            return false;
        }
    }

    *out = result;
    return true;
}