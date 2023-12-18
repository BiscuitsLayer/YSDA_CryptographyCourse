#pragma once

#include <iostream>
#include <array>

class GaloisField {
public:
    // Order = Prime in the power of k,
    // Prime = 2, k = 8
    static constexpr size_t kOrderValue = 1 << 8; // Same as field's size
    static constexpr size_t kModuloValue = kOrderValue - 1;
    static constexpr uint8_t kInv = 255; // invalid power value

    // Primitive element = 2
    static constexpr std::array<uint8_t, kOrderValue> primitive_power_to_number = {
          1,   2,   4,   8,  16,  32,  64, 128, 195,  69, 138, 215, 109, 218, 119, 238, 
         31,  62, 124, 248,  51, 102, 204,  91, 182, 175, 157, 249,  49,  98, 196,  75, 
        150, 239,  29,  58, 116, 232,  19,  38,  76, 152, 243,  37,  74, 148, 235,  21, 
         42,  84, 168, 147, 229,   9,  18,  36,  72, 144, 227,   5,  10,  20,  40,  80, 
        160, 131, 197,  73, 146, 231,  13,  26,  52, 104, 208,  99, 198,  79, 158, 255, 
         61, 122, 244,  43,  86, 172, 155, 245,  41,  82, 164, 139, 213, 105, 210, 103, 
        206,  95, 190, 191, 189, 185, 177, 161, 129, 193,  65, 130, 199,  77, 154, 247, 
         45,  90, 180, 171, 149, 233,  17,  34,  68, 136, 211, 101, 202,  87, 174, 159, 
        253,  57, 114, 228,  11,  22,  44,  88, 176, 163, 133, 201,  81, 162, 135, 205, 
         89, 178, 167, 141, 217, 113, 226,   7,  14,  28,  56, 112, 224,   3,   6,  12, 
         24,  48,  96, 192,  67, 134, 207,  93, 186, 183, 173, 153, 241,  33,  66, 132, 
        203,  85, 170, 151, 237,  25,  50, 100, 200,  83, 166, 143, 221, 121, 242,  39, 
         78, 156, 251,  53, 106, 212, 107, 214, 111, 222, 127, 254,  63, 126, 252,  59, 
        118, 236,  27,  54, 108, 216, 115, 230,  15,  30,  60, 120, 240,  35,  70, 140, 
        219, 117, 234,  23,  46,  92, 184, 179, 165, 137, 209,  97, 194,  71, 142, 223, 
        125, 250,  55, 110, 220, 123, 246,  47,  94, 188, 187, 181, 169, 145, 225,   0,
    };

    static constexpr std::array<uint8_t, kOrderValue> number_to_primitive_power = {
        kInv,  0,   1, 157,   2,  59, 158, 151,   3,  53,  60, 132, 159,  70, 152, 216, 
          4, 118,  54,  38,  61,  47, 133, 227, 160, 181,  71, 210, 153,  34, 217,  16,
          5, 173, 119, 221,  55,  43,  39, 191,  62,  88,  48,  83, 134, 112, 228, 247,
        161,  28, 182,  20,  72, 195, 211, 242, 154, 129,  35, 207, 218,  80,  17, 204,
          6, 106, 174, 164, 120,   9, 222, 237,  56,  67,  44,  31,  40, 109, 192,  77,
         63, 140,  89, 185,  49, 177,  84, 125, 135, 144, 113,  23, 229, 167, 248,  97,
        162, 235,  29,  75, 183, 123,  21,  95,  73,  93, 196, 198, 212,  12, 243, 200,
        155, 149, 130, 214,  36, 225, 208,  14, 219, 189,  81, 245,  18, 240, 205, 202,
          7, 104, 107,  65, 175, 138, 165, 142, 121, 233,  10,  91, 223, 147, 238, 187,
         57, 253,  68,  51,  45, 116,  32, 179,  41, 171, 110,  86, 193,  26,  78, 127,
         64, 103, 141, 137,  90, 232, 186, 146,  50, 252, 178, 115,  85, 170, 126,  25,
        136, 102, 145, 231, 114, 251,  24, 169, 230, 101, 168, 250, 249, 100,  98,  99,
        163, 105, 236,   8,  30,  66,  76, 108, 184, 139, 124, 176,  22, 143,  96, 166,
         74, 234,  94, 122, 197,  92, 199,  11, 213, 148,  13, 224, 244, 188, 201, 239,
        156, 254, 150,  58, 131,  52, 215,  69,  37, 117, 226,  46, 209, 180,  15,  33,
        220, 172, 190,  42,  82,  87, 246, 111,  19,  27, 241, 194, 206, 128, 203,  79,
    };

    class Element {
    public:
        Element(): primitive_power_(0) {}

        explicit Element(const uint8_t number)
        : primitive_power_(number_to_primitive_power[number]) {}

        inline operator uint8_t() { return primitive_power_to_number[primitive_power_]; }

        Element operator*(const Element other);
        Element operator/(const Element other);

    private:
        uint8_t primitive_power_;

        friend std::ostream& operator<<(std::ostream&, const GaloisField::Element);
    };
};