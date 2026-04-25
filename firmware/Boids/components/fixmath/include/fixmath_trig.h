#ifndef FIXMATH_TRIG_H
#define FIXMATH_TRIG_H

#include "fixmath.h"

/**
 * Binary Angular Measurement
 * 0 to 65535 represents 0 to 360 degrees.
 */
typedef uint16_t angle_t;

// Common angles in BAM format
#define ANGLE_0      ((angle_t)0)
#define ANGLE_90     ((angle_t)16384)
#define ANGLE_180    ((angle_t)32768)
#define ANGLE_270    ((angle_t)49152)

/**
 * @brief Calculates the sine of an angle using a lookup table and linear interpolation.
 * @param a Angle in BAM format (0-65535).
 * @return fp_t Result in Q16.16 format.
 */
fp_t fixmath_sin(angle_t a);

/**
 * @brief Calculates the cosine of an angle.
 * @param a Angle in BAM format.
 * @return fp_t Result in Q16.16 format.
 */
fp_t fixmath_cos(angle_t a);
#endif // FIXMATH_TRIG_H