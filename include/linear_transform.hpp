#pragma once

#include <immintrin.h>

#include "context.hpp"
#include "galois_field.hpp"

class LinearTransform {
public:
    static constexpr std::array<uint8_t, KuznechikContext::kBlockSize> coefficients = {
        1, 148, 32, 133, 16, 194, 192, 1, 251, 1, 192, 194, 16, 133, 32, 148
    };

    static inline 
        std::array<
            std::array<
                KuznechikContext::Block, 
            KuznechikContext::kBlockSize * KuznechikContext::kBlockSize>, 
        KuznechikContext::kBlockSize> 
    linear_transform_matrix;

    static inline 
        std::array<
            std::array<
                KuznechikContext::Block, 
            KuznechikContext::kBlockSize * KuznechikContext::kBlockSize>, 
        KuznechikContext::kBlockSize> 
    inverted_linear_transform_matrix;

    static void ForwardPrecompute(KuznechikContext::Block& block);
    static void BackwardPrecompute(KuznechikContext::Block& block);

    static void GenerateLinearTransformMatrices();

    static void Forward(KuznechikContext::Block& block);
    static void Backward(KuznechikContext::Block& block);
};