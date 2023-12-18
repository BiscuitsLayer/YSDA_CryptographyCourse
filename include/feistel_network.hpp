#pragma once

#include "context.hpp"

class FeistelNetwork {
public:
    // Short network: no rhs
    static KuznechikContext::Block Forward(const KuznechikContext::Block& lhs, 
        const KuznechikContext::Block& non_linear_substituion_term);
    static KuznechikContext::Block Backward(const KuznechikContext::Block& lhs, 
        const KuznechikContext::Block& non_linear_substituion_term);

    // Full network: XOR with rhs at the end
    static KuznechikContext::Block Forward(const KuznechikContext::Block& lhs, const KuznechikContext::Block& rhs, 
        const KuznechikContext::Block& non_linear_substituion_term);
};