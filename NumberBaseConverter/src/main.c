//
// Created by regrif07 on 11/3/24.
//

#include <stdio.h>

#include <base_conversions.h>
#include <io_utility.h>

#include <stdlib.h>

ConversionStatus startSingleDecimalToBaseConversion();
ConversionStatus startSingleBaseToDecimalConversion();
void startConversionSession(ConversionStatus (*singleConversionStarter)());

int main(void)
{
    while (true)
    {
        printf("MAIN MENU\n1) From decimal to base\n2) From base to decimal\n3) Exit\n");

        switch (loopReadInteger("> "))
        {
        case 1:
            startConversionSession(&startSingleDecimalToBaseConversion);
            break;

        case 2:
            startConversionSession(&startSingleBaseToDecimalConversion);
            break;

        case 3:
            return EXIT_SUCCESS;

        default:
            printf("Invalid choice.\n");
        }
    }
}

ConversionStatus startSingleDecimalToBaseConversion()
{
    printf("\n");

    const long long decimal = loopReadLongLong("Enter your decimal: ");
    const int base = loopReadInteger("Enter the target base: ");

    ConversionStatus conversionStatus;
    char* conversionResult = decimalToBase(decimal, base, &conversionStatus);
    if (conversionStatus == SUCCESS)
    {
        printf("=> %s\n", conversionResult);
    }

    return conversionStatus;
}

ConversionStatus startSingleBaseToDecimalConversion()
{
    printf("\n");

    char* numberStr = readLine("Enter your number: ", true);

    const int base = loopReadInteger("Enter the base of your number: ");

    ConversionStatus conversionStatus;
    const long long conversionResult = baseToDecimal(numberStr, base, &conversionStatus);
    if (conversionStatus == SUCCESS)
    {
        printf("=> %lld\n", conversionResult);
    }

    free(numberStr);

    return conversionStatus;
}

void startConversionSession(ConversionStatus (*singleConversionStarter)())
{
    while (true)
    {
        switch (singleConversionStarter())
        {
        case INVALID_BASE:
            printf("Error: invalid base.\n");
            continue;

        case INVALID_OPERAND:
            printf("Error: invalid operand.\n");
            continue;

        case UNSUPPORTED_OPERAND:
            printf("Error: this operand is unsupported.\n");
            continue;

        case MEMORY_ERROR:
            printf("Error: memory error occurred while trying to process the conversion.");
            continue;

        case RESULT_OVERFLOW:
            printf("Error: the result of the conversion is too big/small.");
            continue;

        default:
            break;
        }

        if (loopReadInteger("Enter 0 to go back and any other number to continue: ") == 0)
        {
            printf("\n");
            return;
        }
    }
}