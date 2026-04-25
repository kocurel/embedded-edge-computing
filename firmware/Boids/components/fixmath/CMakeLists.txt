idf_component_register(
    SRCS "fixmath.c" "test/test_fixmath.c" "test/fixmath_precision.c"
    REQUIRES unity
    INCLUDE_DIRS "include" "test/include")
