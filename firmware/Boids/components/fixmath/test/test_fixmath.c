#include "fixmath.h"
#include "unity.h"

// Macros for easier reading
#define F(x) FP_FROM_SP(x##f)
#define I(x) FP_FROM_INT(x)

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
    TEST_ASSERT_EQUAL_INT32(0x00010000,  I(1));
    TEST_ASSERT_EQUAL_INT32(0x00000000,  I(0));

    // Negative numbers
    TEST_ASSERT_EQUAL_INT32(-0x00010000, I(-1));

    // Maxim value (2^15 - 1)
    TEST_ASSERT_EQUAL_INT32(0x7FFF0000, I(32767));
}

void test_fixmath_sp_to_fp(void){
    TEST_ASSERT_EQUAL_INT32(0x00008000,  F(0.5));
    TEST_ASSERT_EQUAL_INT32(0x00004000,  F(0.25));
    TEST_ASSERT_EQUAL_INT32(0x000A0000,  F(10.0));
}

void test_fixmath_add(void){
    check_add(I(INT16_MAX), I(0), I(INT16_MAX));
    check_add(I(INT16_MAX), I(INT16_MIN), I(-1));
    check_add(I(555), I(-555), 0);
    
    // Identity property
    check_add(I(1234), 0, I(1234));

    // Commutative property
    check_add(I(2), I(3), I(5));
    check_add(I(3), I(2), I(5));

    // 0.5 (0x8000) + 0.25 (0x4000) = 0.75 (0xC000)
    check_add(0x8000, 0x4000, 0xC000);
}

void test_fixmath_sub(void){
    check_sub(I(INT16_MAX), I(0), I(INT16_MAX));
    check_sub(I(555), I(555), 0);
    check_sub(I(2), I(-2), I(4));
    
    // Identity property
    check_sub(I(1234), 0, I(1234));

    check_sub(I(2), I(3), I(-1));
    check_sub(I(3), I(2), I(1));

    // 0.5 (0x8000) - 0.25 (0x4000) = 0.25 (0x4000)
    check_sub(0x8000, 0x4000, 0x4000);
}

void test_fixmath_wrap_around(void) {
    // Test positive overflow (wrap to negative)
    check_add(0x7FFFFFFF, 1, 0x80000000);
    
    // Test negative overflow (wrap to positive)
    check_sub(0x80000000, 1, 0x7FFFFFFF);
}

void test_fixmath_mult_overflow(void){
    // Test the safe limit (181)
    check_mul(I(181), I(181), I(32761));

    // Test positive saturation (182)
    check_mul(I(182), I(182), I(INT32_MAX));

    // Test negative saturation
    check_mul(I(200), I(-200), I(INT32_MIN));
}

void test_fixmath_mult_underflow(void){
    // Test for 0.1f
    fp_t small_res = fixmath_mul(F(0.1), F(0.1));
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.01f, FP_TO_FLOAT(small_res));

    // Test rounding (epsilon * 0.5 should equal epsilon)
    check_mul(FP_EPSILON, F(0.5), FP_EPSILON);

    // Test underflow (EPSILON * EPSILON is 0)
    check_mul(FP_EPSILON, FP_EPSILON, 0);
}

void test_fixmath_mul(void){
    // Zero property
    check_mul(I(INT16_MAX), 0, 0);
    check_mul(I(INT16_MIN), 0, 0);
    check_mul(0, 0, 0);

    // Identity property
    check_mul(I(INT16_MAX), I(1), I(INT16_MAX));
    check_mul(I(INT16_MIN), I(1), I(INT16_MIN));
    
    // Commutative property
    check_mul(I(2), I(3), I(6));
    check_mul(I(3), I(2), I(6));
    
    // Signed multiplication
    check_mul(I(-2), I(-3), I(6));
    check_mul(I(2), I(-3), I(-6));
    check_mul(I(-2), I(3), I(-6));
    
    // Fractional multiplication
    // 0.5 (0x8000) * 0.5 (0x8000) = 0.5 (0x8000)
    check_mul(0x8000, 0x8000, 0x4000);
}

void test_fixmath_div(void){
    check_div(I(4), I(2), I(2));
    check_div(I(4), I(4), I(1));
    check_div(I(4), I(-4), I(-1));
    check_div(I(4), F(0.5), I(8));
    check_div(0, I(1), 0);
    check_div(I(1), I(2), F(0.5));
    check_div(F(0.5), I(4), F(0.125));

}

void test_fixmath_abs(void){
    // Positive
    check_abs(I(2), I(2));
    check_abs(I(INT16_MAX), I(INT16_MAX));
    
    // Negative
    check_abs(I(-2), I(2));
    check_abs(I(INT16_MIN + 1), I(INT16_MAX));
    
    // Zero
    check_abs(I(0), I(0));

    // Fractions
    check_abs(F(-0.5), F(0.5));
    check_abs(F(0.5), F(0.5));
}

void test_fixmath_sqrt(void){
    // Positive
    check_sqrt(I(4), I(2));
    check_sqrt(I(16), I(4));

    // Zero and one
    check_sqrt(I(0), I(0));
    check_sqrt(I(1), I(1));
    
    // Fractions
    check_sqrt(F(0.25), F(0.5));
    check_sqrt(F(0.0625), F(0.25));
}

#undef F
#undef I