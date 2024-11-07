//
// Created by regrif07 on 11/3/24.
//

#include <stdio.h>

#include <base_conversions.h>
#include <stdlib.h>

int startDecimalToBaseConversion();
int startBaseToDecimalConversion();

int main(void)
{
    printf("Choose the conversion:\n1) From decimal to base\n2) From base to decimal\n> ");
    int userChoice;
    scanf("%d", &userChoice);

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
    printf("Enter your decimal: ");
    int decimal;
    scanf("%d", &decimal);

    printf("Enter the target base: ");
    int base;
    scanf("%d", &base);

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
    char* numberStr = calloc(sizeof(char), 50);
    scanf("%s", numberStr);
    if (!numberStr)
    {
        printf("Invalid input.");
        return EXIT_FAILURE;
    }

    printf("Enter the base of your number: ");
    int base;
    scanf("%d", &base);

    ConversionStatus conversionStatus;
    int conversionResult = baseToDecimal(numberStr, base, &conversionStatus);
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