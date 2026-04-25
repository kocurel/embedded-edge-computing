#include "fixmath.h"
#include "esp_log.h"
#include <math.h> 

static const char *TAG = "FIX_PRECISION";

// Helper macros for easier notation (remember to #undef at the end!)
#define F(x) FP_FROM_SP(x)

static void analyze_mul_precision(float a, float b) {
    float expected = a * b;
    fp_t result_fp = fixmath_mul(F(a), F(b));
    float actual = FP_TO_FLOAT(result_fp);
    
    // Calculate absolute and relative (percentage) error
    float abs_error = fabsf(actual - expected);
    float rel_error_pct = (expected != 0) ? (abs_error / fabsf(expected)) * 100.0f : 0.0f;

    ESP_LOGI(TAG, "%0.4f * %0.4f | Exp: %10.6f | Got: %10.6f | Err: %10.6f (%0.4f%%)", 
             a, b, expected, actual, abs_error, rel_error_pct);
}

void fixmath_run_precision_analysis(void) {
    ESP_LOGI(TAG, "==================================================================");
    ESP_LOGI(TAG, "         FIXED-POINT MULTIPLICATION PRECISION ANALYSIS            ");
    ESP_LOGI(TAG, "==================================================================");

    // Range: "Standard" values used in Boids simulation
    ESP_LOGI(TAG, ">> Mid-range values:");
    analyze_mul_precision(0.5f, 0.5f);
    analyze_mul_precision(0.2f, 0.2f);
    analyze_mul_precision(0.1f, 0.1f);

    // Range: Very small forces (common during Separation behavior)
    ESP_LOGI(TAG, ">> Low-range (Small forces):");
    analyze_mul_precision(0.05f, 0.05f);
    analyze_mul_precision(0.01f, 0.01f);
    analyze_mul_precision(0.005f, 0.005f);

    // Range: Extreme fractions (at the precision floor/noise limit)
    ESP_LOGI(TAG, ">> Extreme low-range (Precision floor):");
    analyze_mul_precision(0.001f, 0.001f);
    analyze_mul_precision(0.0005f, 0.0005f);

    ESP_LOGI(TAG, "==================================================================");
}
#undef F