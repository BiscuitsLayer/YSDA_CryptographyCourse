#pragma once

#include "context.hpp"
#include "galois_field.hpp"

class LinearTransform {
public:
    static constexpr std::array<uint8_t, KuznechikContext::kBlockSize> coefficients = {
        1, 148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148
    };

    static KuznechikContext::Block Forward(KuznechikContext::Block& block);
    static KuznechikContext::Block Backward(KuznechikContext::Block& block);
};