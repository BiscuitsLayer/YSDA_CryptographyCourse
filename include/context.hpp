#pragma once

#include <iostream>
#include <array>
#include <iomanip>
#include <iterator>

class KuznechikContext {
public:
    // Sizes
    static constexpr size_t kBlockSize = 16;    // block size = 128 bits
    static constexpr size_t kKeySize = 32;      // key length = 256 bits

    // Precomputed
    static constexpr size_t kRoundConstantsCount = 32;
    static constexpr size_t kRoundKeysCount = 10;
    static constexpr size_t kRoundKeysFeistelCount = 8;

    // Encrypt / decrypt
    static constexpr size_t kEncryptFeistelFullCount = 9;

    // Subtypes
    struct Block {
        alignas(16) std::array<uint8_t, kBlockSize> data = std::array<uint8_t, kBlockSize>{};

        inline uint8_t& operator[](const size_t index) { return data[index]; }
        inline uint8_t operator[](const size_t index) const { return data[index]; }

        bool operator==(const Block& other) const;

        friend std::ostream& operator<<(std::ostream&, const KuznechikContext::Block&);
    };
    using UserKey = std::array<uint8_t, kKeySize>;

    // Data
    std::array<Block, kRoundConstantsCount> round_constants;
    std::array<Block, kRoundKeysCount> round_keys;

public:
    KuznechikContext(UserKey&& user_key);

    void GenerateRoundConstants();
    void GenerateRoundKeys(UserKey&& user_key);

    void Encrypt(Block& block);
    void Decrypt(Block& block);
};