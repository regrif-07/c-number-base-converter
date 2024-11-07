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
    const int decimal = loopReadInteger("Enter your decimal: ");
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
    // should be reworked
    printf("Enter your number: ");
    char* numberStr = calloc(sizeof(char), 50);
    scanf("%s", numberStr);
    if (!numberStr)
    {
        printf("Invalid input.");
        return EXIT_FAILURE;
    }

    const int base = loopReadInteger("Enter the base of your number: ");

    ConversionStatus conversionStatus;
    const int conversionResult = baseToDecimal(numberStr, base, &conversionStatus);
    switch (conversionStatus)
    {
    case SUCCESS:
        printf("Result: %d\n", conversionResult);
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