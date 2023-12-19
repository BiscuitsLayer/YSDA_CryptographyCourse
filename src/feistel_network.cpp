#include "feistel_network.hpp"
#include "non_linear_substitution.hpp"
#include "linear_transform.hpp"

void FeistelNetwork::Forward(KuznechikContext::Block& lhs, 
    const KuznechikContext::Block& non_linear_substituion_term) {
    // Apply XOR and non-linear transform consistently
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        lhs[byte_index] = NonlinearSubstitution::Forward(
            lhs[byte_index] ^ 
            non_linear_substituion_term[byte_index]
        );
    }
            
    // Apply linear transform
    LinearTransform::Forward(lhs);
}

void FeistelNetwork::Backward(KuznechikContext::Block& lhs, 
    const KuznechikContext::Block& non_linear_substituion_term) {
    // Apply inverse linear transform
    LinearTransform::Backward(lhs);

    // Apply XOR and inverse non-linear transform consistently
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        lhs[byte_index] = NonlinearSubstitution::Backward(lhs[byte_index]) ^ 
            non_linear_substituion_term[byte_index];
    }
}

void FeistelNetwork::Forward(KuznechikContext::Block& lhs, const KuznechikContext::Block& rhs, 
    const KuznechikContext::Block& non_linear_substituion_term) {
    // Apply XOR and non-linear transform consistently
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        lhs[byte_index] = NonlinearSubstitution::Forward(
            lhs[byte_index] ^ 
            non_linear_substituion_term[byte_index]
        );
    }
            
    // Apply linear transform
    LinearTransform::Forward(lhs);

    // XOR left block with the right one
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        lhs[byte_index] ^= rhs[byte_index];
    }
}