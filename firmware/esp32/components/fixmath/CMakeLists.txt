idf_component_register(
    SRCS 
    "fixmath.c" "fixmath_trig.c" 
    
    "test/test_fixmath.c" 
    "test/fixmath_precision.c"
    "test/test_trig.c"

    REQUIRES unity
    INCLUDE_DIRS "include" "test/include")
