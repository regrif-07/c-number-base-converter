//
// Created by regrif07 on 11/3/24.
//

#include <base_conversions.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <string_utility.h>

#include "numbers_utility.h"

constexpr int MIN_BASE = 2;
constexpr int MAX_BASE = 36;

constexpr int BUFFER_SIZE = 65; // just a general guess for good buffer size deducted from (LLONG_MAX -> binary) size

// ONLY UPPERCASE CHARACTER-DIGITS ARE SUPPORTED!
// NEGATIVE NUMBERS ARE NOT SUPPORTED!

bool isValidBase(const int base)
{
    return base >= MIN_BASE && base <= MAX_BASE;
}

// will NOT check if digit is correct with respect to the base
char getDigitByReminder(const long long reminder)
{
    return (reminder < 10) ? (char)('0' + reminder) : (char)('A' + (reminder - 10));
}

// returns -1 in case digit is invalid
int getDigitValue(const char digit)
{
    if (digit >= '0' && digit <= '9')
    {
        return digit - '0';
    }
    if (digit >= 'A' && digit <= 'Z')
    {
        return digit - 'A' + 10; // letter digits are representing values greater than 9, so we add 10
    }

    return -1;
}

char* decimalToBase(const long long decimal, const int base, ConversionStatus* conversionStatus)
{
    if (!isValidBase(base))
    {
        *conversionStatus = INVALID_BASE;
        return nullptr;
    }

    if (decimal < 0)
    {
        *conversionStatus = UNSUPPORTED_OPERAND;
        return nullptr;
    }

    char* resultBuffer = calloc(sizeof(char), BUFFER_SIZE);
    if (!resultBuffer)
    {
        *conversionStatus = MEMORY_ERROR;
        return nullptr;
    }

    int resultSize = 0;
    long long quotient = decimal;
    while (quotient > 0)
    {
        if (resultSize > BUFFER_SIZE - 2) // index = size - 1, and we need to keep 1 for \0
        {
            free(resultBuffer);
            *conversionStatus = MEMORY_ERROR;
            return nullptr;
        }

        resultBuffer[resultSize++] = getDigitByReminder(quotient % base);
        quotient /= base;
    }
    resultBuffer[resultSize++] = '\0';

    // reallocate memory to not waste unused buffer memory
    char* resultReallocated = realloc(resultBuffer, resultSize);
    if (!resultReallocated)
    {
        free(resultBuffer);
        *conversionStatus = MEMORY_ERROR;
        return nullptr;
    }

    reverseStringInPlace(resultReallocated);
    *conversionStatus = SUCCESS;

    // there is no memory leak here, realloc() analysis is incorrect
    // we cannot free(resultBuffer) here because it will result in a double free in case of realloc() success
    return resultReallocated;
}

// use the return value only after checking the conversionStatus
long long baseToDecimal(const char* numberStr, const int base, ConversionStatus* conversionStatus)
{
    if (!numberStr)
    {
        *conversionStatus = INVALID_OPERAND;
        return 0;
    }

    if (!isValidBase(base))
    {
        *conversionStatus = INVALID_BASE;
        return 0;
    }

    const int numberStrLen = (int)(strlen(numberStr));
    long long result = 0;
    for (int digitIndex = 0; digitIndex < numberStrLen - 1; ++digitIndex)
    {
        const int digitValue = getDigitValue(numberStr[digitIndex]);
        if (digitValue >= base)
        {
            *conversionStatus = INVALID_OPERAND;
            return 0;
        }

        bool isOverflow = false;

        long long toAdd;
        isOverflow = !safeLongLongPow(base, numberStrLen - digitIndex - 2, &toAdd);
        isOverflow = !safeLongLongMultiply(digitValue, toAdd, &toAdd);
        isOverflow = !safeLongLongAdd(result, toAdd, &result);
        if (isOverflow)
        {
            *conversionStatus = RESULT_OVERFLOW;
            return 0;
        }
    }

    *conversionStatus = SUCCESS;
    return result;
}