#include "feistel_network.hpp"
#include "non_linear_substitution.hpp"
#include "linear_transform.hpp"

void FeistelNetwork::Forward() {
    // Subtract two because we already computed first two keys
    for (size_t index = 0, new_index = 1; index < (KuznechikContext::kRoundKeysCount - 2) / 2; ++index, ++new_index) {
        size_t left_round_key_index = 2 * index;
        size_t right_round_key_index = left_round_key_index + 1;

        KuznechikContext::Block left_round_key = KuznechikContext::round_keys[left_round_key_index];
        KuznechikContext::Block right_round_key = KuznechikContext::round_keys[right_round_key_index];
        
        KuznechikContext::Block new_round_key;
    
        for (size_t round_index = 0; round_index < kRoundsCount; ++round_index) {
            // Apply non-linear transform
            for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
                size_t round_constant_index = index * 8 + round_index;
                
                uint8_t lhs = left_round_key[byte_index];
                uint8_t rhs = KuznechikContext::round_constants[round_constant_index][byte_index];

                // new_round_key[byte_index] = NonlinearSubstitution::Forward(
                //     left_round_key[byte_index] ^ 
                //     KuznechikContext::round_constants[round_constant_index][byte_index]
                // );
                new_round_key[byte_index] = NonlinearSubstitution::Forward(
                    lhs ^ rhs
                );
            }
            
            // Apply linear transform
            LinearTransform::Forward(new_round_key);

            // XOR left block with the right one
            for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
                new_round_key[byte_index] ^= right_round_key[byte_index];
            }

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