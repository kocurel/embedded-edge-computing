import math

# Configuration
TABLE_SIZE = 1024  # Number of points in 360 degrees
SCALE = 65536     # 2^16 for Q16.16

def generate_sin_table():
    with open("sin_lut.h", "w") as f:
        f.write("// Auto-generated Sine Table for Q16.16 fixed-point\n")
        f.write(f"#ifndef SIN_LUT_H\n#define SIN_LUT_H\n\n")
        f.write(f"#include <stdint.h>\n\n")
        f.write(f"#define SIN_LUT_SIZE {TABLE_SIZE}\n\n")
        f.write(f"static const int32_t sin_lut[{TABLE_SIZE}] = {{\n")
        
        for i in range(TABLE_SIZE):
            # Calculate angle in radians
            angle = (2 * math.pi * i) / TABLE_SIZE
            # Calculate sine and scale to Q16.16
            val = int(math.sin(angle) * SCALE)
            
            f.write(f"    {val},")
            if (i + 1) % 8 == 0:  # Formatting: 8 numbers per line
                f.write("\n")
                
        f.write("};\n\n#endif\n")

if __name__ == "__main__":
    generate_sin_table()
    print("sin_lut.h generated successfully!")
