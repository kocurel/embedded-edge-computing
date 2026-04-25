#include "fixmath.h"
#include "unity.h"

// ---- HELPER FUNCTIONS ----

static void check_add(fp_t a, fp_t b, fp_t expected){
    TEST_ASSERT_EQUAL_INT32(expected, fixmath_add(a, b));
}

static void check_sub(fp_t a, fp_t b, fp_t expected){
    TEST_ASSERT_EQUAL_INT32(expected, fixmath_sub(a, b));
}

static void check_mul(fp_t a, fp_t b, fp_t expected){
    TEST_ASSERT_EQUAL_INT32(expected, fixmath_mul(a, b));
}

static void check_abs(fp_t a, fp_t expected){
    TEST_ASSERT_EQUAL_INT32(expected, fixmath_abs(a));
}

static void check_sqrt(fp_t a, fp_t expected){
    TEST_ASSERT_EQUAL_INT32(expected, fixmath_sqrt(a));
}

static void check_div(fp_t a, fp_t b, fp_t expected){
    TEST_ASSERT_EQUAL_INT32(expected, fixmath_div(a, b));
}

// ---- TESTS ----

void test_fixmath_int_to_fp(void){
    // Positive numbers and zero
    TEST_ASSERT_EQUAL_INT32(0x00010000,  FP_FROM_INT(1));
    TEST_ASSERT_EQUAL_INT32(0x00000000,  FP_FROM_INT(0));

    // Negative numbers
    TEST_ASSERT_EQUAL_INT32(-0x00010000, FP_FROM_INT(-1));

    // Maxim value (2^15 - 1)
    TEST_ASSERT_EQUAL_INT32(0x7FFF0000, FP_FROM_INT(32767));
}

void test_fixmath_sp_to_fp(void){
    TEST_ASSERT_EQUAL_INT32(0x00008000,  FP_FROM_SP(0.5f));
    TEST_ASSERT_EQUAL_INT32(0x00004000,  FP_FROM_SP(0.25f));
    TEST_ASSERT_EQUAL_INT32(0x000A0000,  FP_FROM_SP(10.f));
}

void test_fixmath_add(void){
    check_add(FP_FROM_INT(INT16_MAX), FP_FROM_INT(0), FP_FROM_INT(INT16_MAX));
    check_add(FP_FROM_INT(INT16_MAX), FP_FROM_INT(INT16_MIN), FP_FROM_INT(-1));
    check_add(FP_FROM_INT(555), FP_FROM_INT(-555), 0);
    
    // Identity property
    check_add(FP_FROM_INT(1234), 0, FP_FROM_INT(1234));

    // Commutative property
    check_add(FP_FROM_INT(2), FP_FROM_INT(3), FP_FROM_INT(5));
    check_add(FP_FROM_INT(3), FP_FROM_INT(2), FP_FROM_INT(5));

    // 0.5 (0x8000) + 0.25 (0x4000) = 0.75 (0xC000)
    check_add(0x8000, 0x4000, 0xC000);
}

void test_fixmath_sub(void){
    check_sub(FP_FROM_INT(INT16_MAX), FP_FROM_INT(0), FP_FROM_INT(INT16_MAX));
    check_sub(FP_FROM_INT(555), FP_FROM_INT(555), 0);
    check_sub(FP_FROM_INT(2), FP_FROM_INT(-2), FP_FROM_INT(4));
    
    // Identity property
    check_sub(FP_FROM_INT(1234), 0, FP_FROM_INT(1234));

    check_sub(FP_FROM_INT(2), FP_FROM_INT(3), FP_FROM_INT(-1));
    check_sub(FP_FROM_INT(3), FP_FROM_INT(2), FP_FROM_INT(1));

    // 0.5 (0x8000) - 0.25 (0x4000) = 0.25 (0x4000)
    check_sub(0x8000, 0x4000, 0x4000);
}

void test_fixmath_wrap_around(void) {
    // Test positive overflow (wrap to negative)
    check_add(0x7FFFFFFF, 1, 0x80000000);
    
    // Test negative overflow (wrap to positive)
    check_sub(0x80000000, 1, 0x7FFFFFFF);
}

void test_fixmath_mul(void){
    // Zero property
    check_mul(FP_FROM_INT(INT16_MAX), FP_FROM_INT(0), FP_FROM_INT(0));
    check_mul(FP_FROM_INT(INT16_MIN), FP_FROM_INT(0), FP_FROM_INT(0));
    check_mul(FP_FROM_INT(0), FP_FROM_INT(0), FP_FROM_INT(0));

    // Identity property
    check_mul(FP_FROM_INT(INT16_MAX), FP_FROM_INT(1), FP_FROM_INT(INT16_MAX));
    check_mul(FP_FROM_INT(INT16_MIN), FP_FROM_INT(1), FP_FROM_INT(INT16_MIN));
    
    // Commutative property
    check_mul(FP_FROM_INT(2), FP_FROM_INT(3), FP_FROM_INT(6));
    check_mul(FP_FROM_INT(3), FP_FROM_INT(2), FP_FROM_INT(6));
    
    // Signed multiplication
    check_mul(FP_FROM_INT(-2), FP_FROM_INT(-3), FP_FROM_INT(6));
    check_mul(FP_FROM_INT(2), FP_FROM_INT(-3), FP_FROM_INT(-6));
    check_mul(FP_FROM_INT(-2), FP_FROM_INT(3), FP_FROM_INT(-6));
    
    // Fractional multiplication
    // 0.5 (0x8000) * 0.5 (0x8000) = 0.5 (0x8000)
    check_mul(0x8000, 0x8000, 0x4000);
}

void test_fixmath_div(void){
    check_div(FP_FROM_INT(4), FP_FROM_INT(2), FP_FROM_INT(2));
    check_div(FP_FROM_INT(4), FP_FROM_INT(4), FP_FROM_INT(1));
    check_div(FP_FROM_INT(4), FP_FROM_INT(-4), FP_FROM_INT(-1));
    check_div(FP_FROM_INT(4), FP_FROM_SP(0.5f), FP_FROM_INT(8));
    check_div(FP_FROM_INT(0), FP_FROM_INT(1), FP_FROM_INT(0));
    check_div(FP_FROM_INT(1), FP_FROM_INT(2), FP_FROM_SP(0.5f));
    check_div(FP_FROM_SP(0.5f), FP_FROM_INT(4), FP_FROM_SP(0.125f));

}

void test_fixmath_abs(void){
    // Positive
    check_abs(FP_FROM_INT(2), FP_FROM_INT(2));
    check_abs(FP_FROM_INT(INT16_MAX), FP_FROM_INT(INT16_MAX));
    
    // Negative
    check_abs(FP_FROM_INT(-2), FP_FROM_INT(2));
    check_abs(FP_FROM_INT(INT16_MIN + 1), FP_FROM_INT(INT16_MAX));
    
    // Zero
    check_abs(FP_FROM_INT(0), FP_FROM_INT(0));

    // Fractions
    check_abs(FP_FROM_SP(-0.5f), FP_FROM_SP(0.5f));
    check_abs(FP_FROM_SP(0.5f), FP_FROM_SP(0.5f));
}

void test_fixmath_sqrt(void){
    // Positive
    check_sqrt(FP_FROM_INT(4), FP_FROM_INT(2));
    check_sqrt(FP_FROM_INT(16), FP_FROM_INT(4));

    // Zero and one
    check_sqrt(FP_FROM_INT(0), FP_FROM_INT(0));
    check_sqrt(FP_FROM_INT(1), FP_FROM_INT(1));
    
    // Fractions
    check_sqrt(FP_FROM_SP(0.25f), FP_FROM_SP(0.5f));
    check_sqrt(FP_FROM_SP(0.0625f), FP_FROM_SP(0.25f));
}
