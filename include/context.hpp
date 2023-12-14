#pragma once

#include <iostream>
#include <array>
#include <iomanip>

class KuznechikContext {
public:
    static constexpr size_t kBlockSize = 16;
    static constexpr size_t kRoundConstantsCount = 32;

    struct Block {
        std::array<uint8_t, kBlockSize> data = std::array<uint8_t, kBlockSize>{};

        inline uint8_t& operator[](const size_t index) { return data[index]; }
        inline uint8_t operator[](const size_t index) const { return data[index]; }

        bool operator==(const Block& other) const;

        friend std::ostream& operator<<(std::ostream&, const KuznechikContext::Block&);
    };

    static inline std::array<Block, kRoundConstantsCount> round_constants;

    static void GenerateRoundConstants();
};