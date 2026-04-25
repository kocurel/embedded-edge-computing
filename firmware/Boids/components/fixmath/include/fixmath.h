#ifndef FIXMATH_H
#define FIXMATH_H

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

// Calculates sum of two Q16.16 fixed-point numbers
// inlining to avoid function call overhead cost
static inline fp_t fixmath_add(fp_t a, fp_t b){
    return a + b;
}
// Calculates difference of two Q16.16 fixed-point numbers
// inlining to avoid function call overhead cost
static inline fp_t fixmath_sub(fp_t a, fp_t b){
    return a - b;
}

// Calculates product of two Q16.16 fixed-point numbers
// inlining to avoid function call overhead cost
static inline fp_t fixmath_mul(fp_t a, fp_t b){
    const int64_t product = (int64_t)a * (int64_t)b;
    // Add 0.5 to round the result
    return (fp_t)((product + 32768) >> 16);
}

// Calculates absolute value of a Q16.16 fixed-point number
// Assumes input is not INT32_MIN to avoid overflow.
static inline fp_t fixmath_abs(fp_t a){
    return (a < 0) ? (-a) : a;
}

static inline fp_t fixmath_div(fp_t a, fp_t b){
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