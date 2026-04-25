#include "fixmath.h"

fp_t fixmath_sqrt(fp_t a) {
    // Return 0 for negative numbers as square root is undefined in real numbers
    if (a < 0) return 0; 
    if (a == 0) return 0;

    uint32_t op = (uint32_t)a;
    uint32_t res = 0;
    
    /* Using Digit-by-digit algorithm */
    uint32_t one = 1u << 30;

    while (one > op) {
        one >>= 2;
    }

    while (one != 0) {
        if (op >= res + one) {
            op -= res + one;
            res = (res >> 1) + one;
        } else {
            res >>= 1;
        }
        one >>= 2;
    }

    /* * In Q16.16 format: sqrt(x * 2^16) = sqrt(x) * 2^8.
     * To return the result in Q16.16, we must shift the calculated integer root 
     * by an additional 8 bits to the left.
     */
    return (fp_t)(res << 8);
}