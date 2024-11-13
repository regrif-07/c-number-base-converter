//
// Created by regrif07 on 11/13/24.
//

#include <base_conversions.h>

#include <unity.h>

#include <limits.h>
#include <stdlib.h>

void setUp(void)
{
}

void tearDown(void)
{
}

// helper to verify conversion round-trip
void testConversionRoundTrip(const long long decimal, const int base)
{
    ConversionStatus status;
    char* baseStr = decimalToBase(decimal, base, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);

    const long long resultDecimal = baseToDecimal(baseStr, base, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(decimal, resultDecimal);

    free(baseStr);
}

// Test valid conversions
void testRoundTripsValid()
{
    testConversionRoundTrip(0, 2);
    testConversionRoundTrip(1, 2);
    testConversionRoundTrip(-1, 16);
    testConversionRoundTrip(255, 16);
    testConversionRoundTrip(-12345, 36);
    testConversionRoundTrip(LLONG_MAX, 2);
    // testConversionRoundTrip(LLONG_MIN, 10); // not supported due to difference between LLONG_MIN and LLONG_MAX
}

// Test invalid base
void testInvalidBase()
{
    ConversionStatus status;
    const char* result = decimalToBase(123, 1, &status);
    TEST_ASSERT_EQUAL(INVALID_BASE, status);
    TEST_ASSERT_NULL(result);

    result = decimalToBase(123, 37, &status);
    TEST_ASSERT_EQUAL(INVALID_BASE, status);
    TEST_ASSERT_NULL(result);

    long long decimal = baseToDecimal("123", 1, &status);
    TEST_ASSERT_EQUAL(INVALID_BASE, status);

    decimal = baseToDecimal("123", 37, &status);
    TEST_ASSERT_EQUAL(INVALID_BASE, status);
}

// Test edge cases (e.g., zero, min, max)
void testEdgeCases()
{
    ConversionStatus status;

    // Zero conversion
    char* zeroStr = decimalToBase(0, 10, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL_STRING("0", zeroStr);
    free(zeroStr);

    // Maximum positive integer
    char* maxStr = decimalToBase(LLONG_MAX, 16, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    const long long maxVal = baseToDecimal(maxStr, 16, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(LLONG_MAX, maxVal);
    free(maxStr);

    // Minimum negative integer
    char* minStr = decimalToBase(LLONG_MIN, 10, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    const long long minVal = baseToDecimal(minStr, 10, &status);
    TEST_ASSERT_EQUAL(RESULT_OVERFLOW, status);
    free(minStr);
}

// Test non-numeric input and invalid characters
void testInvalidCharacters()
{
    ConversionStatus status;
    long long result = baseToDecimal("123G", 16, &status); // 'G' is invalid in base 16
    TEST_ASSERT_EQUAL(INVALID_OPERAND, status);

    result = baseToDecimal("XYZ", 10, &status); // All letters invalid in base 10
    TEST_ASSERT_EQUAL(INVALID_OPERAND, status);
}

// Test overflow in power, multiplication, addition operations
void testOverflowHandling()
{
    ConversionStatus status;

    // Overflow in power, e.g., large number in a large base
    long long result = baseToDecimal("ZZZZZZZZZZZZZZZZZZZ", 36, &status); // Likely overflow in decimal
    TEST_ASSERT_EQUAL(RESULT_OVERFLOW, status);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(testRoundTripsValid);
    RUN_TEST(testInvalidBase);
    RUN_TEST(testEdgeCases);
    RUN_TEST(testInvalidCharacters);
    RUN_TEST(testOverflowHandling);

    return UNITY_END();
}
