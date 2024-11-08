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
    if (digit >= 'a' && digit <= 'z')
    {
        return digit - 'a' + 10; // letter digits are representing values greater than 9, so we add 10
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

    char* resultBuffer = calloc(sizeof(char), BUFFER_SIZE);
    if (!resultBuffer)
    {
        *conversionStatus = MEMORY_ERROR;
        return nullptr;
    }

    const bool isNegativeDecimal = decimal < 0;
    long long quotient = isNegativeDecimal ? -decimal : decimal;
    int resultSize = 0;

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

    const size_t reallocatedSize = isNegativeDecimal ? resultSize + 1 : resultSize;
    // reallocate memory to not waste unused buffer memory
    char* resultReallocated = realloc(resultBuffer, reallocatedSize);
    if (!resultReallocated)
    {
        free(resultBuffer);
        *conversionStatus = MEMORY_ERROR;
        return nullptr;
    }

    if (isNegativeDecimal)
    {
        resultReallocated[reallocatedSize - 2] = '-';
    }
    resultReallocated[reallocatedSize - 1] = '\0';

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

    const bool isNegativeNumber = numberStr[0] == '-';
    const int numberStrLen = (int)(strlen(numberStr));

    long long result = 0;
    for (int digitIndex = isNegativeNumber ? 1 : 0; digitIndex < numberStrLen - 1; ++digitIndex)
    {
        const int digitValue = getDigitValue(numberStr[digitIndex]);
        if (digitValue >= base)
        {
            *conversionStatus = INVALID_OPERAND;
            return 0;
        }

        long long toAdd;
        const bool isPowOverflow = !safeLongLongPow(base, numberStrLen - digitIndex - 2, &toAdd);
        const bool isMultiplicationOverflow = !safeLongLongMultiply(digitValue, toAdd, &toAdd);
        const bool isAdditionOverflow = !safeLongLongAdd(result, toAdd, &result);
        if (isPowOverflow || isMultiplicationOverflow || isAdditionOverflow)
        {
            *conversionStatus = RESULT_OVERFLOW;
            return 0;
        }
    }

    if (isNegativeNumber)
    {
        result *= -1;
    }

    *conversionStatus = SUCCESS;
    return result;
}