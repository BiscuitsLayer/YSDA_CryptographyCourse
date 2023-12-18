#include "context.hpp"
#include "linear_transform.hpp"
#include "feistel_network.hpp"

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
            auto new_round_key = FeistelNetwork::Forward(left_round_key, right_round_key, non_linear_substituion_term);

            // Swap halves
            right_round_key = left_round_key;
            left_round_key = new_round_key;
        }

        size_t new_left_round_key_index = 2 * new_index;
        size_t new_right_round_key_index = new_left_round_key_index + 1;
        
        KuznechikContext::round_keys[new_left_round_key_index] = left_round_key;
        KuznechikContext::round_keys[new_right_round_key_index] = right_round_key;
    }
}

void KuznechikContext::Encrypt(KuznechikContext::Block& block) {

}

void KuznechikContext::Decrypt(Block& block) {

}