#ifndef FIXMATH_H
#define FIXMATH_H

#include "assert.h"
#include <stdint.h>

// Arithemtic bitshift assert to make sure signed shifting works
_Static_assert((-8 >> 1) == -4, "Compiler must use arithmetic shift for fixmath to work.");

// Fixed-Point type (Q16.16)
typedef int32_t fp_t;

// Macros for static initialization
#define FP_FROM_INT(i) ((fp_t)(((uint32_t)(i)) << 16))
#define FP_FROM_SP(i) ((fp_t)(((float)(i)) * 65536.0f))

// Macros for convertion to standard C types
#define FP_TO_INT(a) ((int32_t)((a) >> 16))
#define FP_TO_FLOAT(a) ((float)(a) / 65536.0f)

// Defined mathematical constants
#define FP_PI          205887L  // 3.14159... * 65536
#define FP_ONE         65536L   // 1.0
#define FP_HALF        32768L   // 0.5
#define FP_EPSILON     1L       // Smallest possible fraction 

/**
 * @brief Adds two Q16.16 numbers.
 * @note This function has no overflow check.
 */
static inline fp_t fixmath_add(fp_t a, fp_t b){
    return a + b;
}

/**
 * @brief Subtracts b from a (Q16.16).
 * @note This function has no overflow check.
 */
static inline fp_t fixmath_sub(fp_t a, fp_t b){
    return a - b;
}

/**
 * @brief Multiplies two Q16.16 numbers with rounding and saturation.
 * @note Uses rounding towards positive infinity (adds 0.5 before shift)
 */
static inline fp_t fixmath_mul(fp_t a, fp_t b){
    const int64_t product = (int64_t)a * b;
    // Add 0.5 to round the result towards positive infinity
    int64_t result = (product + 32768) >> 16;

    if (result > INT32_MAX) return INT32_MAX;
    if (result < INT32_MIN) return INT32_MIN;

    return (fp_t)result;
}

/**
 * @brief The absolute value of a Q16.16 fixed-point number
 * @note Assumes input is not INT32_MIN.
 */ 
static inline fp_t fixmath_abs(fp_t a){
    return (a < 0) ? (-a) : a;
}

/**
 * @brief Divides a by b (Q16.16)
 * @note ESP32 has no hardware 64-bit division 
 * so it results in a call to gcc's __divdi3.
 * 
 * @warning *Do not use division unless it's necessary.*
 */
static inline fp_t fixmath_div(fp_t a, fp_t b){
    assert(b != 0);
    if (b == 0) return 0;

    // Scale the numerator to 64-bit to preserve fractional parts 
    // during the division process.
    const int64_t numerator = (int64_t)a << 16;

    // The result of (a * 2^16) / b is already in Q16.16 format.
    // (2^32 / 2^16 = 2^16)
    return (fp_t)(numerator / b);
}

// Calculates square root of a Q16.16 fixed-point number
fp_t fixmath_sqrt(fp_t a);


#endif // FIXMATH_H