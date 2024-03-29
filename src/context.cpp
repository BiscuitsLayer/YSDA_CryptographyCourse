#include "context.hpp"
#include "feistel_network.hpp"
#include "galois_field.hpp"
#include "linear_transform.hpp"

std::ostream& operator<<(std::ostream& stream, const KuznechikContext::Block& block) {
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

bool KuznechikContext::Block::operator==(const Block& other) const {
    for (size_t index = 0; index < kBlockSize; ++index) {
        if (data[index] != other.data[index]) {
            return false;
        }
    }
    return true;
}

KuznechikContext::KuznechikContext(UserKey&& user_key) {
#ifdef OPTIMIZATION_LEVEL_1
    GaloisField::GenerateMultiplicationResults();
#endif // OPTIMIZATION_LEVEL_1

#ifdef OPTIMIZATION_LEVEL_2
    LinearTransform::GenerateLinearTransformMatrices();
#endif // OPTIMIZATION_LEVEL_2

    GenerateRoundConstants();
    GenerateRoundKeys(std::move(user_key));
}

void KuznechikContext::GenerateRoundConstants() {
    int counter = 1;

    for (auto& round_constant : round_constants) {
        round_constant[0] = counter++;
        LinearTransform::Forward(round_constant);
    }
}

void KuznechikContext::GenerateRoundKeys(UserKey&& user_key) {
    // First two keys are two halves of the user key
    std::move(user_key.begin(), user_key.begin() + kBlockSize, round_keys[0].data.begin());
    std::move(user_key.begin() + kBlockSize, user_key.end(), round_keys[1].data.begin());

    // Subtract two because we already computed first two keys
    for (size_t index = 0, new_index = 1; index < (KuznechikContext::kRoundKeysCount - 2) / 2; ++index, ++new_index) {
        size_t left_round_key_index = 2 * index;
        size_t right_round_key_index = left_round_key_index + 1;

        // Divide user key in two parts
        KuznechikContext::Block left_round_key = KuznechikContext::round_keys[left_round_key_index];
        KuznechikContext::Block right_round_key = KuznechikContext::round_keys[right_round_key_index];

        // Apply Feistel network 4 * 8 times (to use all round constants)
        for (size_t round_index = 0; round_index < kRoundKeysFeistelCount; ++round_index) {
            size_t round_constant_index = index * 8 + round_index;
            auto non_linear_substituion_term = KuznechikContext::round_constants[round_constant_index];

            // Output is the new round key
            auto left_round_key_copy = left_round_key;
            FeistelNetwork::Forward(left_round_key, right_round_key, non_linear_substituion_term);

            // Swap halves (left half is already updated)
            right_round_key = left_round_key_copy;
        }

        size_t new_left_round_key_index = 2 * new_index;
        size_t new_right_round_key_index = new_left_round_key_index + 1;
        
        KuznechikContext::round_keys[new_left_round_key_index] = left_round_key;
        KuznechikContext::round_keys[new_right_round_key_index] = right_round_key;
    }
}

void KuznechikContext::Encrypt(KuznechikContext::Block& block) {
    auto&& new_block = std::move(block);

    // Apply short Feistel network 9 times
    for (size_t round_index = 0; round_index < kEncryptFeistelFullCount; ++round_index) {
        const auto& non_linear_substituion_term = KuznechikContext::round_keys[round_index];
        FeistelNetwork::Forward(new_block, non_linear_substituion_term);
    }

    // Apply XOR with the last round key
    const auto& last_round_key = KuznechikContext::round_keys.back();
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        new_block[byte_index] ^= last_round_key[byte_index];
    }

    block = std::move(new_block);
}

void KuznechikContext::Decrypt(Block& block) {
    auto&& new_block = std::move(block);

    // Apply XOR with the last round key
    const auto& last_round_key = KuznechikContext::round_keys.back();
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        new_block[byte_index] ^= last_round_key[byte_index];
    }

    // Apply inverted short Feistel network 9 times
    for (size_t round_index = kEncryptFeistelFullCount - 1; round_index + 1 > 0; --round_index) {
        const auto& non_linear_substituion_term = KuznechikContext::round_keys[round_index];
        FeistelNetwork::Backward(new_block, non_linear_substituion_term);
    }

    block = std::move(new_block);
}