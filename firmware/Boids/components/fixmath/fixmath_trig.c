#include "fixmath_trig.h"
#include "fixmath_sin_lut.h"

fp_t fixmath_sin(angle_t a){
    return (fp_t)(sin_lut[a >> 6]);
}
fp_t fixmath_cos(angle_t a){
    // cosine is shfted 90 degrees
    // a bit mask is used to discard the 10th bit
    return (fp_t)(sin_lut[((a >> 6) + 256) & 0x3FF]);
}