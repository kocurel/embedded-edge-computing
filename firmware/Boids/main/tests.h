#ifndef TESTS_H
#define TESTS_H

#include "unity.h"
#include "test_fixmath.h"
#include "fixmath.h"
#include "fixmath_precision.h"
#include "test_trig.h"

void fixmath_unity_tests(void){
    UNITY_BEGIN();
    
    RUN_TEST(test_fixmath_int_to_fp);
    RUN_TEST(test_fixmath_sp_to_fp);
    RUN_TEST(test_fixmath_add);
    RUN_TEST(test_fixmath_sub);
    RUN_TEST(test_fixmath_wrap_around);
    RUN_TEST(test_fixmath_mult_underflow);
    RUN_TEST(test_fixmath_mul);
    RUN_TEST(test_fixmath_sqrt);
    RUN_TEST(test_fixmath_div);

    RUN_TEST(fixmath_test_sine);
    RUN_TEST(fixmath_test_cosine);

    UNITY_END();
}


void run_tests(void){
    fixmath_unity_tests();
    fixmath_run_precision_analysis();

}



#endif // TESTS_H