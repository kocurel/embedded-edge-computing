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
#define ANGLE_30      ((angle_t)5461)
#define ANGLE_60      ((angle_t)10922)
#define ANGLE_90     ((angle_t)16384)
#define ANGLE_180    ((angle_t)32768)
#define ANGLE_270    ((angle_t)49152)

#define DEG_TO_BAM_FACTOR 11930114 // (65536 / 360)

/**
 * @brief Calculates an angle in Binary Angular Measurement from degrees
 */
static inline angle_t degrees_to_BAM(fp_t degrees) {
    const fp_t circle_deg = FP_FROM_INT(360);
    // Normalize to range the [0, 360)
    while (degrees >= circle_deg) degrees -= circle_deg;
    while (degrees < 0)           degrees += circle_deg;

    // The result is a fraction of 0..0.999 in Q16.16
    // Casting to uint16_t scales it to 0..65535
    return (angle_t)fixmath_div(degrees, circle_deg);
}

/**
 * @brief Calculates an angle in Binary Angular Measurement from radians
 */
static inline angle_t rad_to_BAM(fp_t radians) {
    const fp_t two_pi = FP_FROM_SP(6.283185f);
    // Normalize to range the [0, 2pi)
    while (radians >= two_pi) radians -= two_pi;
    while (radians < 0)       radians += two_pi;

    return (angle_t)fixmath_div(radians, two_pi);
}

/**
 * @brief Calculates the sine of an angle using a lookup table.
 * @param a Angle in BAM format (0-65535).
 */
fp_t fixmath_sin(angle_t a);

/**
 * @brief Calculates the cosine of an angle.
 * @param a Angle in BAM format.
 */
fp_t fixmath_cos(angle_t a);

#endif // FIXMATH_TRIG_H