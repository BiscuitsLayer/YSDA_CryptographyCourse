#include <iostream>
#include <array>
#include <iomanip>

class KuznechikContext {
public:
    static constexpr size_t kBlockSize = 16;
    struct Block {
        std::array<uint8_t, kBlockSize> data = std::array<uint8_t, kBlockSize>{};

        inline uint8_t& operator[](const size_t index) {
            return data[index];
        }

        inline uint8_t operator[](const size_t index) const {
            return data[index];
        }

        bool operator==(const Block& other) const {
            for (size_t index = 0; index < kBlockSize; ++index) {
                if (data[index] != other.data[index]) {
                    return false;
                }
            }
            return true;
        }
    };
};

std::ostream& operator<<(std::ostream& stream, KuznechikContext::Block& block) {
    stream << '{';
    for (size_t index = 0; index < KuznechikContext::kBlockSize; ++index) {
        stream << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(block[index]);
        if (index != KuznechikContext::kBlockSize - 1) {
            stream << ", ";
        } else {
            stream << '}';
        }
    }

    return stream;
}

class GaloisField {
public:
    // Order = Prime ^ k,
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
        Element()
        : primitive_power_(0) {}

        explicit Element(const uint8_t number)
        : primitive_power_(number_to_primitive_power[number]) {}

        operator uint8_t() {
            return primitive_power_to_number[primitive_power_];
        }

        Element operator*(const Element other) {
            Element ans;
            if ((primitive_power_ == kInv) || (other.primitive_power_ == kInv)) {
                ans.primitive_power_ = kInv;
            } else {
                ans.primitive_power_ = (primitive_power_ + other.primitive_power_) % GaloisField::kModuloValue;
            }
            return ans;
        }

        // Element operator/(const Element other) {
        //     Element ans;
        //     ans.primitive_power_ = (primitive_power_ - other.primitive_power_) % GaloisField::kModuloValue;
        //     return ans;
        // }

    private:
        uint8_t primitive_power_;

        friend std::ostream& operator<<(std::ostream&, const GaloisField::Element);
    };
};

std::ostream& operator<<(std::ostream& stream, const GaloisField::Element element) {
    stream << static_cast<int>(GaloisField::primitive_power_to_number[element.primitive_power_]);
    return stream;
}

class LinearTransform {
public:
    static constexpr std::array<uint8_t, KuznechikContext::kBlockSize> coefficients = {
        1, 148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148
    };

    KuznechikContext::Block operator()(KuznechikContext::Block& block) const {
        uint8_t result = 0;

        for (size_t shift_index = 0; shift_index < KuznechikContext::kBlockSize; ++shift_index) {
            for (size_t coef_index = 0; coef_index < LinearTransform::coefficients.size(); ++coef_index) { 

                size_t byte_index = (coef_index + shift_index) % KuznechikContext::kBlockSize;
                GaloisField::Element byte{block[byte_index]};
                GaloisField::Element coef{LinearTransform::coefficients[coef_index]};

                result ^= coef * byte;
            }

            block[shift_index] = result;
            result = 0;
        }

        return block;
    }
};

class NonlinearSubstitution {
public:
    static constexpr std::array<uint8_t, GaloisField::kOrderValue> nonlinear_substitution = {
        0xfc, 0xee, 0xdd, 0x11, 0xcf, 0x6e, 0x31, 0x16, 0xfb, 0xc4, 0xfa, 0xda, 0x23, 0xc5, 0x04, 0x4d,
        0xe9, 0x77, 0xf0, 0xdb, 0x93, 0x2e, 0x99, 0xba, 0x17, 0x36, 0xf1, 0xbb, 0x14, 0xcd, 0x5f, 0xc1,
        0xf9, 0x18, 0x65, 0x5a, 0xe2, 0x5c, 0xef, 0x21, 0x81, 0x1c, 0x3c, 0x42, 0x8b, 0x01, 0x8e, 0x4f,
        0x05, 0x84, 0x02, 0xae, 0xe3, 0x6a, 0x8f, 0xa0, 0x06, 0x0b, 0xed, 0x98, 0x7f, 0xd4, 0xd3, 0x1f,
        0xeb, 0x34, 0x2c, 0x51, 0xea, 0xc8, 0x48, 0xab, 0xf2, 0x2a, 0x68, 0xa2, 0xfd, 0x3a, 0xce, 0xcc,
        0xb5, 0x70, 0x0e, 0x56, 0x08, 0x0c, 0x76, 0x12, 0xbf, 0x72, 0x13, 0x47, 0x9c, 0xb7, 0x5d, 0x87,
        0x15, 0xa1, 0x96, 0x29, 0x10, 0x7b, 0x9a, 0xc7, 0xf3, 0x91, 0x78, 0x6f, 0x9d, 0x9e, 0xb2, 0xb1,
        0x32, 0x75, 0x19, 0x3d, 0xff, 0x35, 0x8a, 0x7e, 0x6d, 0x54, 0xc6, 0x80, 0xc3, 0xbd, 0x0d, 0x57,
        0xdf, 0xf5, 0x24, 0xa9, 0x3e, 0xa8, 0x43, 0xc9, 0xd7, 0x79, 0xd6, 0xf6, 0x7c, 0x22, 0xb9, 0x03,
        0xe0, 0x0f, 0xec, 0xde, 0x7a, 0x94, 0xb0, 0xbc, 0xdc, 0xe8, 0x28, 0x50, 0x4e, 0x33, 0x0a, 0x4a,
        0xa7, 0x97, 0x60, 0x73, 0x1e, 0x00, 0x62, 0x44, 0x1a, 0xb8, 0x38, 0x82, 0x64, 0x9f, 0x26, 0x41,
        0xad, 0x45, 0x46, 0x92, 0x27, 0x5e, 0x55, 0x2f, 0x8c, 0xa3, 0xa5, 0x7d, 0x69, 0xd5, 0x95, 0x3b,
        0x07, 0x58, 0xb3, 0x40, 0x86, 0xac, 0x1d, 0xf7, 0x30, 0x37, 0x6b, 0xe4, 0x88, 0xd9, 0xe7, 0x89,
        0xe1, 0x1b, 0x83, 0x49, 0x4c, 0x3f, 0xf8, 0xfe, 0x8d, 0x53, 0xaa, 0x90, 0xca, 0xd8, 0x85, 0x61,
        0x20, 0x71, 0x67, 0xa4, 0x2d, 0x2b, 0x09, 0x5b, 0xcb, 0x9b, 0x25, 0xd0, 0xbe, 0xe5, 0x6c, 0x52,
        0x59, 0xa6, 0x74, 0xd2, 0xe6, 0xf4, 0xb4, 0xc0, 0xd1, 0x66, 0xaf, 0xc2, 0x39, 0x4b, 0x63, 0xb6,
    };

    static constexpr std::array<uint8_t, GaloisField::kOrderValue> inverted_nonlinear_substitution = {
        0xa5, 0x2d, 0x32, 0x8f, 0x0e, 0x30, 0x38, 0xc0, 0x54, 0xe6, 0x9e, 0x39, 0x55, 0x7e, 0x52, 0x91,
        0x64, 0x03, 0x57, 0x5a, 0x1c, 0x60, 0x07, 0x18, 0x21, 0x72, 0xa8, 0xd1, 0x29, 0xc6, 0xa4, 0x3f,
        0xe0, 0x27, 0x8d, 0x0c, 0x82, 0xea, 0xae, 0xb4, 0x9a, 0x63, 0x49, 0xe5, 0x42, 0xe4, 0x15, 0xb7,
        0xc8, 0x06, 0x70, 0x9d, 0x41, 0x75, 0x19, 0xc9, 0xaa, 0xfc, 0x4d, 0xbf, 0x2a, 0x73, 0x84, 0xd5,
        0xc3, 0xaf, 0x2b, 0x86, 0xa7, 0xb1, 0xb2, 0x5b, 0x46, 0xd3, 0x9f, 0xfd, 0xd4, 0x0f, 0x9c, 0x2f,
        0x9b, 0x43, 0xef, 0xd9, 0x79, 0xb6, 0x53, 0x7f, 0xc1, 0xf0, 0x23, 0xe7, 0x25, 0x5e, 0xb5, 0x1e,
        0xa2, 0xdf, 0xa6, 0xfe, 0xac, 0x22, 0xf9, 0xe2, 0x4a, 0xbc, 0x35, 0xca, 0xee, 0x78, 0x05, 0x6b,
        0x51, 0xe1, 0x59, 0xa3, 0xf2, 0x71, 0x56, 0x11, 0x6a, 0x89, 0x94, 0x65, 0x8c, 0xbb, 0x77, 0x3c,
        0x7b, 0x28, 0xab, 0xd2, 0x31, 0xde, 0xc4, 0x5f, 0xcc, 0xcf, 0x76, 0x2c, 0xb8, 0xd8, 0x2e, 0x36,
        0xdb, 0x69, 0xb3, 0x14, 0x95, 0xbe, 0x62, 0xa1, 0x3b, 0x16, 0x66, 0xe9, 0x5c, 0x6c, 0x6d, 0xad,
        0x37, 0x61, 0x4b, 0xb9, 0xe3, 0xba, 0xf1, 0xa0, 0x85, 0x83, 0xda, 0x47, 0xc5, 0xb0, 0x33, 0xfa,
        0x96, 0x6f, 0x6e, 0xc2, 0xf6, 0x50, 0xff, 0x5d, 0xa9, 0x8e, 0x17, 0x1b, 0x97, 0x7d, 0xec, 0x58,
        0xf7, 0x1f, 0xfb, 0x7c, 0x09, 0x0d, 0x7a, 0x67, 0x45, 0x87, 0xdc, 0xe8, 0x4f, 0x1d, 0x4e, 0x04,
        0xeb, 0xf8, 0xf3, 0x3e, 0x3d, 0xbd, 0x8a, 0x88, 0xdd, 0xcd, 0x0b, 0x13, 0x98, 0x02, 0x93, 0x80,
        0x90, 0xd0, 0x24, 0x34, 0xcb, 0xed, 0xf4, 0xce, 0x99, 0x10, 0x44, 0x40, 0x92, 0x3a, 0x01, 0x26,
        0x12, 0x1a, 0x48, 0x68, 0xf5, 0x81, 0x8b, 0xc7, 0xd6, 0x20, 0x0a, 0x08, 0x00, 0x4c, 0xd7, 0x74,
    };
};