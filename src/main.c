//
// Created by regrif07 on 11/3/24.
//

#include <stdio.h>

#include <base_conversions.h>
#include <io_utility.h>

#include <stdlib.h>

int startDecimalToBaseConversion();
int startBaseToDecimalConversion();

int main(void)
{
    printf("Choose the conversion:\n1) From decimal to base\n2) From base to decimal\n");
    const int userChoice = loopReadInteger("> ");

    switch (userChoice)
    {
    case 1: return startDecimalToBaseConversion();
    case 2: return startBaseToDecimalConversion();
    default:
        printf("Invalid choice.\n");
        return EXIT_FAILURE;
    }
}

int startDecimalToBaseConversion()
{
    const long long decimal = loopReadLongLong("Enter your decimal: ");
    const int base = loopReadInteger("Enter the target base: ");

    ConversionStatus conversionStatus;
    char* conversionResult = decimalToBase(decimal, base, &conversionStatus);
    switch (conversionStatus)
    {
    case SUCCESS:
        printf("Result: %s\n", conversionResult);
        return EXIT_SUCCESS;

    case INVALID_BASE:
        printf("Target base is invalid.");
        break;

    case INVALID_OPERAND:
        printf("Decimal is invalid.");
        break;

    case UNSUPPORTED_OPERAND:
        printf("This type of decimal is not supported.");
        break;

    case MEMORY_ERROR:
        printf("Unexpected error occurred.");
        break;

    case RESULT_OVERFLOW:
        printf("The result of the conversion is too big.");
        break;
    }

    return EXIT_FAILURE;
}

int startBaseToDecimalConversion()
{
    printf("Enter your number: ");
    char* numberStr = nullptr;
    size_t numberStrLen;
    if (getline(&numberStr, &numberStrLen, stdin) < 0) // if it failed to read a line...
    {
        printf("Unexpected error occurred.");
        return EXIT_FAILURE;
    }

    const int base = loopReadInteger("Enter the base of your number: ");

    ConversionStatus conversionStatus;
    const long long conversionResult = baseToDecimal(numberStr, base, &conversionStatus);
    switch (conversionStatus)
    {
    case SUCCESS:
        printf("Result: %lld\n", conversionResult);
        return EXIT_SUCCESS;

    case INVALID_BASE:
        printf("Target base is invalid.");
        break;

    case INVALID_OPERAND:
        printf("Entered number is invalid.");
        break;

    case UNSUPPORTED_OPERAND:
        printf("This type of number is not supported.");
        break;

    case MEMORY_ERROR:
        printf("Unexpected error occurred.");
        break;

    case RESULT_OVERFLOW:
        printf("The result of the conversion is too big.");
        break;
    }

    return EXIT_FAILURE;
}