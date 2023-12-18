#include "algorithm.hpp"
#include <gtest/gtest.h>
#include <vector>

// Check round constants
// Article: https://habr.com/ru/articles/459004/
TEST(LinearTransform, RoundConstantsCheck) {
    std::vector<std::pair<KuznechikContext::Block, KuznechikContext::Block>> input_to_output = {
        {
            {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x01, 0x94, 0x84, 0xdd, 0x10, 0xbd, 0x27, 0x5d, 0xb8, 0x7a, 0x48, 0x6c, 0x72, 0x76, 0xa2, 0x6e}
        },
        {
            {0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x02, 0xeb, 0xcb, 0x79, 0x20, 0xb9, 0x4e, 0xba, 0xb3, 0xf4, 0x90, 0xd8, 0xe4, 0xec, 0x87, 0xdc}
        },
        {
            {0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x03, 0x7f, 0x4f, 0xa4, 0x30, 0x04, 0x69, 0xe7, 0x0b, 0x8e, 0xd8, 0xb4, 0x96, 0x9a, 0x25, 0xb2}
        },
        {
            {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x04, 0x15, 0x55, 0xf2, 0x40, 0xb1, 0x9c, 0xb7, 0xa5, 0x2b, 0xe3, 0x73, 0x0b, 0x1b, 0xcd, 0x7b}
        },
        {
            {0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x05, 0x81, 0xd1, 0x2f, 0x50, 0x0c, 0xbb, 0xea, 0x1d, 0x51, 0xab, 0x1f, 0x79, 0x6d, 0x6f, 0x15}
        },
        {
            {0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x06, 0xfe, 0x9e, 0x8b, 0x60, 0x08, 0xd2, 0x0d, 0x16, 0xdf, 0x73, 0xab, 0xef, 0xf7, 0x4a, 0xa7}
        },
        {
            {0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x07, 0x6a, 0x1a, 0x56, 0x70, 0xb5, 0xf5, 0x50, 0xae, 0xa5, 0x3b, 0xc7, 0x9d, 0x81, 0xe8, 0xc9}
        },
        {
            {0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x08, 0x2a, 0xaa, 0x27, 0x80, 0xa1, 0xfb, 0xad, 0x89, 0x56, 0x05, 0xe6, 0x16, 0x36, 0x59, 0xf6}
        },
        {
            {0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x09, 0xbe, 0x2e, 0xfa, 0x90, 0x1c, 0xdc, 0xf0, 0x31, 0x2c, 0x4d, 0x8a, 0x64, 0x40, 0xfb, 0x98}
        },
        {
            {0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x0a, 0xc1, 0x61, 0x5e, 0xa0, 0x18, 0xb5, 0x17, 0x3a, 0xa2, 0x95, 0x3e, 0xf2, 0xda, 0xde, 0x2a}
        },
        {
            {0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x0b, 0x55, 0xe5, 0x83, 0xb0, 0xa5, 0x92, 0x4a, 0x82, 0xd8, 0xdd, 0x52, 0x80, 0xac, 0x7c, 0x44}
        },
        {
            {0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x0c, 0x3f, 0xff, 0xd5, 0xc0, 0x10, 0x67, 0x1a, 0x2c, 0x7d, 0xe6, 0x95, 0x1d, 0x2d, 0x94, 0x8d}
        },
        {
            {0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x0d, 0xab, 0x7b, 0x08, 0xd0, 0xad, 0x40, 0x47, 0x94, 0x07, 0xae, 0xf9, 0x6f, 0x5b, 0x36, 0xe3}
        },
        {
            {0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x0e, 0xd4, 0x34, 0xac, 0xe0, 0xa9, 0x29, 0xa0, 0x9f, 0x89, 0x76, 0x4d, 0xf9, 0xc1, 0x13, 0x51}
        },
        {
            {0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x0f, 0x40, 0xb0, 0x71, 0xf0, 0x14, 0x0e, 0xfd, 0x27, 0xf3, 0x3e, 0x21, 0x8b, 0xb7, 0xb1, 0x3f}
        },
        {
            {0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x10, 0x54, 0x97, 0x4e, 0xc3, 0x81, 0x35, 0x99, 0xd1, 0xac, 0x0a, 0x0f, 0x2c, 0x6c, 0xb2, 0x2f}
        },
        {
            {0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x11, 0xc0, 0x13, 0x93, 0xd3, 0x3c, 0x12, 0xc4, 0x69, 0xd6, 0x42, 0x63, 0x5e, 0x1a, 0x10, 0x41}
        },
        {
            {0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x12, 0xbf, 0x5c, 0x37, 0xe3, 0x38, 0x7b, 0x23, 0x62, 0x58, 0x9a, 0xd7, 0xc8, 0x80, 0x35, 0xf3}
        },
        {
            {0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x13, 0x2b, 0xd8, 0xea, 0xf3, 0x85, 0x5c, 0x7e, 0xda, 0x22, 0xd2, 0xbb, 0xba, 0xf6, 0x97, 0x9d}
        },
        {
            {0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x14, 0x41, 0xc2, 0xbc, 0x83, 0x30, 0xa9, 0x2e, 0x74, 0x87, 0xe9, 0x7c, 0x27, 0x77, 0x7f, 0x54}
        },
        {
            {0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x15, 0xd5, 0x46, 0x61, 0x93, 0x8d, 0x8e, 0x73, 0xcc, 0xfd, 0xa1, 0x10, 0x55, 0x01, 0xdd, 0x3a}
        },
        {
            {0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x16, 0xaa, 0x09, 0xc5, 0xa3, 0x89, 0xe7, 0x94, 0xc7, 0x73, 0x79, 0xa4, 0xc3, 0x9b, 0xf8, 0x88}
        },
        {
            {0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x17, 0x3e, 0x8d, 0x18, 0xb3, 0x34, 0xc0, 0xc9, 0x7f, 0x09, 0x31, 0xc8, 0xb1, 0xed, 0x5a, 0xe6}
        },
        {
            {0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x18, 0x7e, 0x3d, 0x69, 0x43, 0x20, 0xce, 0x34, 0x58, 0xfa, 0x0f, 0xe9, 0x3a, 0x5a, 0xeb, 0xd9}
        },
        {
            {0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x19, 0xea, 0xb9, 0xb4, 0x53, 0x9d, 0xe9, 0x69, 0xe0, 0x80, 0x47, 0x85, 0x48, 0x2c, 0x49, 0xb7}
        },
        {
            {0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x1a, 0x95, 0xf6, 0x10, 0x63, 0x99, 0x80, 0x8e, 0xeb, 0x0e, 0x9f, 0x31, 0xde, 0xb6, 0x6c, 0x05}
        },
        {
            {0x1b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x1b, 0x01, 0x72, 0xcd, 0x73, 0x24, 0xa7, 0xd3, 0x53, 0x74, 0xd7, 0x5d, 0xac, 0xc0, 0xce, 0x6b}
        },
        {
            {0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x1c, 0x6b, 0x68, 0x9b, 0x03, 0x91, 0x52, 0x83, 0xfd, 0xd1, 0xec, 0x9a, 0x31, 0x41, 0x26, 0xa2}
        },
        {
            {0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x1d, 0xff, 0xec, 0x46, 0x13, 0x2c, 0x75, 0xde, 0x45, 0xab, 0xa4, 0xf6, 0x43, 0x37, 0x84, 0xcc}
        },
        {
            {0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x1e, 0x80, 0xa3, 0xe2, 0x23, 0x28, 0x1c, 0x39, 0x4e, 0x25, 0x7c, 0x42, 0xd5, 0xad, 0xa1, 0x7e}
        },
        {
            {0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x1f, 0x14, 0x27, 0x3f, 0x33, 0x95, 0x3b, 0x64, 0xf6, 0x5f, 0x34, 0x2e, 0xa7, 0xdb, 0x03, 0x10}
        },
        {
            {0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x20, 0xa8, 0xed, 0x9c, 0x45, 0xc1, 0x6a, 0xf1, 0x61, 0x9b, 0x14, 0x1e, 0x58, 0xd8, 0xa7, 0x5e}
        },
    };

    // Check forward transform
    for (const auto& [input, output] : input_to_output) {
        KuznechikContext::Block modified_input = input;
        LinearTransform::Forward(modified_input);
        EXPECT_EQ(modified_input, output);
    }

    // Check backward transform
    for (const auto& [input, output] : input_to_output) {
        KuznechikContext::Block modified_output = output;
        LinearTransform::Backward(modified_output);
        EXPECT_EQ(modified_output, input);
    }
}

// Check round keys
// Article: https://habr.com/ru/articles/459004/
TEST(LinearTransform, RoundKeysCheck) {
    KuznechikContext::UserKey user_key = {
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
        0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
        0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
    };

    std::vector<KuznechikContext::Block> correct_round_keys = {
        {0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88},
        {0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01, 0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe},
        {0x44, 0x8c, 0xc7, 0x8c, 0xef, 0x6a, 0x8d, 0x22, 0x43, 0x43, 0x69, 0x15, 0x53, 0x48, 0x31, 0xdb},
        {0x04, 0xfd, 0x9f, 0x0a, 0xc4, 0xad, 0xeb, 0x15, 0x68, 0xec, 0xcf, 0xe9, 0xd8, 0x53, 0x45, 0x3d},
        {0xac, 0xf1, 0x29, 0xf4, 0x46, 0x92, 0xe5, 0xd3, 0x28, 0x5e, 0x4a, 0xc4, 0x68, 0x64, 0x64, 0x57},
        {0x1b, 0x58, 0xda, 0x34, 0x28, 0xe8, 0x32, 0xb5, 0x32, 0x64, 0x5c, 0x16, 0x35, 0x94, 0x07, 0xbd},
        {0xb1, 0x98, 0x00, 0x5a, 0x26, 0x27, 0x57, 0x70, 0xde, 0x45, 0x87, 0x7e, 0x75, 0x40, 0xe6, 0x51},
        {0x84, 0xf9, 0x86, 0x22, 0xa2, 0x91, 0x2a, 0xd7, 0x3e, 0xdd, 0x9f, 0x7b, 0x01, 0x25, 0x79, 0x5a},
        {0x17, 0xe5, 0xb6, 0xcd, 0x73, 0x2f, 0xf3, 0xa5, 0x23, 0x31, 0xc7, 0x78, 0x53, 0xe2, 0x44, 0xbb},
        {0x43, 0x40, 0x4a, 0x8e, 0xa8, 0xba, 0x5d, 0x75, 0x5b, 0xf4, 0xbc, 0x16, 0x74, 0xdd, 0xe9, 0x72},
    };

    KuznechikContext::GenerateRoundConstants();
    KuznechikContext::GenerateRoundKeys(std::move(user_key));

    for (size_t round_key_index = 0; round_key_index < KuznechikContext::kRoundKeysCount; ++round_key_index) {
        EXPECT_EQ(KuznechikContext::round_keys[round_key_index], correct_round_keys[round_key_index]);
    }
}