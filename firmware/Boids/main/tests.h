#ifndef TESTS_H
#define TESTS_H

#include "unity.h"
#include "test_fixmath.h"
#include "fixmath.h"

void run_tests(void){
    UNITY_BEGIN();
    
    RUN_TEST(test_fixmath_int_to_fp);
    RUN_TEST(test_fixmath_sp_to_fp);
    RUN_TEST(test_fixmath_add);
    RUN_TEST(test_fixmath_sub);
    RUN_TEST(test_fixmath_wrap_around);
    RUN_TEST(test_fixmath_mul);
    RUN_TEST(test_fixmath_sqrt);
    RUN_TEST(test_fixmath_div);

    UNITY_END();
}

#endif // TESTS_H