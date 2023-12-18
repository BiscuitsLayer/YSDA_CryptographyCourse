#pragma once

#include "context.hpp"

class FeistelNetwork {
public:
    static KuznechikContext::Block Forward(const KuznechikContext::Block& lhs, const KuznechikContext::Block& rhs, 
        const KuznechikContext::Block& non_linear_substituion_term);
};