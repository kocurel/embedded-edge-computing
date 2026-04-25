#include "test_trig.h"
#include "fixmath_trig.h"
#include "unity.h"

#define F(x) FP_FROM_SP(x##f)

void fixmath_test_sine(void){
    TEST_ASSERT_EQUAL_INT32(0, fixmath_sin(0));
    TEST_ASSERT_INT32_WITHIN(150, F(0.5), fixmath_sin(ANGLE_30));
    TEST_ASSERT_INT32_WITHIN(150, F(0.86602540378), fixmath_sin(ANGLE_60));
    TEST_ASSERT_EQUAL_INT32(F(1.0), fixmath_sin(ANGLE_90));
    TEST_ASSERT_EQUAL_INT32(0, fixmath_sin(ANGLE_180));
    TEST_ASSERT_EQUAL_INT32(F(-1.0), fixmath_sin(ANGLE_270));
}
void fixmath_test_cosine(void) {
    TEST_ASSERT_EQUAL_INT32(F(1.0), fixmath_cos(0));
    TEST_ASSERT_INT32_WITHIN(150, F(0.86602540378), fixmath_cos(ANGLE_30));
    TEST_ASSERT_INT32_WITHIN(150, F(0.5), fixmath_cos(ANGLE_60));
    TEST_ASSERT_EQUAL_INT32(0, fixmath_cos(ANGLE_90));
    TEST_ASSERT_EQUAL_INT32(F(-1.0), fixmath_cos(ANGLE_180));
    TEST_ASSERT_EQUAL_INT32(0, fixmath_cos(ANGLE_270));
}

#undef F