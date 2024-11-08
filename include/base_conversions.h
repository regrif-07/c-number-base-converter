//
// Created by regrif07 on 11/3/24.
//

#pragma once

typedef enum
{
    SUCCESS,
    INVALID_BASE,
    INVALID_OPERAND,
    UNSUPPORTED_OPERAND,
    MEMORY_ERROR,
    RESULT_OVERFLOW,
} ConversionStatus;

char* decimalToBase(const long long decimal, const int base, ConversionStatus* conversionStatus);
long long baseToDecimal(const char* numberStr, const int base, ConversionStatus* conversionStatus);
