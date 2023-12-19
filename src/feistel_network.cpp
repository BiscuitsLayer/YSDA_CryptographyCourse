#include "feistel_network.hpp"
#include "non_linear_substitution.hpp"
#include "linear_transform.hpp"

KuznechikContext::Block FeistelNetwork::Forward(const KuznechikContext::Block& lhs, 
    const KuznechikContext::Block& non_linear_substituion_term) {
    KuznechikContext::Block ans = lhs;

    // Apply XOR and non-linear transform consistently
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        ans[byte_index] = NonlinearSubstitution::Forward(
            ans[byte_index] ^ 
            non_linear_substituion_term[byte_index]
        );
    }
            
    // Apply linear transform
    LinearTransform::Forward(ans);

    return ans;
}

KuznechikContext::Block FeistelNetwork::Backward(const KuznechikContext::Block& lhs, 
    const KuznechikContext::Block& non_linear_substituion_term) {
    KuznechikContext::Block ans = lhs;

    // Apply inverse linear transform
    LinearTransform::Backward(ans);

    // Apply XOR and inverse non-linear transform consistently
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        ans[byte_index] = NonlinearSubstitution::Backward(ans[byte_index]) ^ 
            non_linear_substituion_term[byte_index];
    }

    return ans;
}

KuznechikContext::Block FeistelNetwork::Forward(const KuznechikContext::Block& lhs, const KuznechikContext::Block& rhs, 
    const KuznechikContext::Block& non_linear_substituion_term) {
    KuznechikContext::Block ans;

    // Apply XOR and non-linear transform consistently
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        ans[byte_index] = NonlinearSubstitution::Forward(
            lhs[byte_index] ^ 
            non_linear_substituion_term[byte_index]
        );
    }
            
    // Apply linear transform
    LinearTransform::Forward(ans);

    // XOR left block with the right one
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        ans[byte_index] ^= rhs[byte_index];
    }

    return ans;
}