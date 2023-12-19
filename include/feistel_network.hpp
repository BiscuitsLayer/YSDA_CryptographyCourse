#pragma once

#include "context.hpp"

class FeistelNetwork {
public:
    // Short network: no rhs
    static void Forward(KuznechikContext::Block& lhs, 
        const KuznechikContext::Block& non_linear_substituion_term);
    static void Backward(KuznechikContext::Block& lhs, 
        const KuznechikContext::Block& non_linear_substituion_term);

    // Full network: XOR with rhs at the end
    static void Forward(KuznechikContext::Block& lhs, const KuznechikContext::Block& rhs, 
        const KuznechikContext::Block& non_linear_substituion_term);
};