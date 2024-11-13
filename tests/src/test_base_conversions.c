//
// Created by regrif07 on 11/13/24.
//

#include <base_conversions.h>

#include <unity.h>

#include <limits.h>
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

// Helper to verify conversion round-trip
void test_conversion_round_trip(long long decimal, int base) {
    ConversionStatus status = SUCCESS;
    char* baseStr = decimalToBase(decimal, base, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);

    long long resultDecimal = baseToDecimal(baseStr, base, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(decimal, resultDecimal);

    free(baseStr);
}

// Test valid conversions
void test_decimalToBase_baseToDecimal_valid() {
    test_conversion_round_trip(0, 2);
    test_conversion_round_trip(1, 2);
    test_conversion_round_trip(-1, 16);
    test_conversion_round_trip(255, 16);
    test_conversion_round_trip(-12345, 36);
    test_conversion_round_trip(LLONG_MAX, 2);
    test_conversion_round_trip(LLONG_MIN, 10);
}

// Test invalid base
void test_invalid_base() {
    ConversionStatus status;
    char* result = decimalToBase(123, 1, &status);
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
void test_edge_cases() {
    ConversionStatus status;

    // Zero conversion
    char* zeroStr = decimalToBase(0, 10, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL_STRING("0", zeroStr);
    free(zeroStr);

    // Maximum positive integer
    char* maxStr = decimalToBase(LLONG_MAX, 16, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    long long maxVal = baseToDecimal(maxStr, 16, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(LLONG_MAX, maxVal);
    free(maxStr);

    // Minimum negative integer
    char* minStr = decimalToBase(LLONG_MIN, 10, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    long long minVal = baseToDecimal(minStr, 10, &status);
    TEST_ASSERT_EQUAL(SUCCESS, status);
    TEST_ASSERT_EQUAL(LLONG_MIN, minVal);
    free(minStr);
}

// Test non-numeric input and invalid characters
void test_invalid_characters() {
    ConversionStatus status;
    long long result = baseToDecimal("123G", 16, &status); // 'G' is invalid in base 16
    TEST_ASSERT_EQUAL(INVALID_OPERAND, status);

    result = baseToDecimal("XYZ", 10, &status); // All letters invalid in base 10
    TEST_ASSERT_EQUAL(INVALID_OPERAND, status);
}

// Test memory error handling (simulated by very large buffer usage)
void test_buffer_overflow_handling() {
    ConversionStatus status;
    char* result = decimalToBase(LLONG_MAX, 2, &status); // Testing near buffer limit
    TEST_ASSERT_EQUAL(SUCCESS, status);
    free(result);
}

// Test overflow in power, multiplication, addition operations
void test_overflow_handling() {
    ConversionStatus status;

    // Overflow in power, e.g., large number in a large base
    long long result = baseToDecimal("ZZZZZZZZZZZ", 36, &status); // Likely overflow in decimal
    TEST_ASSERT_EQUAL(RESULT_OVERFLOW, status);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_decimalToBase_baseToDecimal_valid);
    RUN_TEST(test_invalid_base);
    RUN_TEST(test_edge_cases);
    RUN_TEST(test_invalid_characters);
    RUN_TEST(test_buffer_overflow_handling);
    RUN_TEST(test_overflow_handling);

    return UNITY_END();
}
