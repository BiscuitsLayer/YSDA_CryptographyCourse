#include "linear_transform.hpp"

void LinearTransform::ForwardPrecompute(KuznechikContext::Block& block) {
    uint8_t result = 0;

    for (size_t shift_index = 0; shift_index < KuznechikContext::kBlockSize; ++shift_index) {
        for (size_t coef_index = 0; coef_index < LinearTransform::coefficients.size(); ++coef_index) { 
            size_t byte_index = (coef_index + shift_index) % KuznechikContext::kBlockSize;

            #ifdef OPTIMIZATION_LEVEL_1
                result ^= GaloisField::multiplication_results[block[byte_index]][LinearTransform::coefficients[coef_index]];
            #else // OPTIMIZATION_LEVEL_1
                GaloisField::Element byte{block[byte_index]};
                GaloisField::Element coef{LinearTransform::coefficients[coef_index]};
                result ^= static_cast<uint8_t>(coef * byte);
            #endif // OPTIMIZATION_LEVEL_1
        }

        block[shift_index] = result;
        result = 0;
    }
}

void LinearTransform::BackwardPrecompute(KuznechikContext::Block& block) {
    uint8_t result = 0;

    for (size_t shift_index = KuznechikContext::kBlockSize - 1; shift_index + 1 > 0 ; --shift_index) {
        for (size_t coef_index = 0; coef_index < LinearTransform::coefficients.size(); ++coef_index) { 
            size_t byte_index = (coef_index + shift_index + 1) % KuznechikContext::kBlockSize;
            
            #ifdef OPTIMIZATION_LEVEL_1
                result ^= GaloisField::multiplication_results[block[byte_index]][LinearTransform::coefficients[KuznechikContext::kBlockSize - coef_index - 1]];
            #else // OPTIMIZATION_LEVEL_1
                GaloisField::Element byte{block[byte_index]};
                GaloisField::Element coef{LinearTransform::coefficients[KuznechikContext::kBlockSize - coef_index - 1]};
                result ^= static_cast<uint8_t>(coef * byte);
            #endif // OPTIMIZATION_LEVEL_1
        }

        block[shift_index] = result;
        result = 0;
    }
}

void LinearTransform::GenerateLinearTransformMatrices() {
    // Iterate over every byte in the block and every possible value for it
    for (size_t byte_index = 0; byte_index < KuznechikContext::kBlockSize; ++byte_index) {
        for (size_t value = 0; value < GaloisField::kOrderValue; ++value) {
            KuznechikContext::Block block;
            block[byte_index] = value;

            // Apply linear transform for that simplest element and save the result
            auto block_forward = block;
            LinearTransform::ForwardPrecompute(block_forward);
            linear_transform_matrix[byte_index][value] = block_forward;

            // Apply inverted linear transform for that simplest element and save the result
            auto block_backward = block;
            LinearTransform::BackwardPrecompute(block_backward);
            inverted_linear_transform_matrix[byte_index][value] = block_backward;
        }
    }
}

void LinearTransform::Forward(KuznechikContext::Block& block) {
#ifndef OPTIMIZATION_LEVEL_2
    return ForwardPrecompute(block);
#else // OPTIMIZATION_LEVEL_2
    KuznechikContext::Block ans;

    for (size_t shift_index = 0; shift_index < KuznechikContext::kBlockSize; ++shift_index) {
        // Load elements
        __m128 ans_elements = _mm_loadu_ps((float*)ans.data.data());
        __m128 linear_transform_matrix_elements = _mm_loadu_ps((float*)linear_transform_matrix[shift_index][block[shift_index]].data.data());

        // Apply XOR
        __m128 xor_result_elements = _mm_xor_ps(ans_elements, linear_transform_matrix_elements);

        // Store elements
        _mm_storeu_ps((float*)ans.data.data(), xor_result_elements);
    }

    block = std::move(ans);
#endif // OPTIMIZATION_LEVEL_2
}

void LinearTransform::Backward(KuznechikContext::Block& block) {
#ifndef OPTIMIZATION_LEVEL_2
    return BackwardPrecompute(block);
#else // OPTIMIZATION_LEVEL_2
    KuznechikContext::Block ans;

    for (size_t shift_index = 0; shift_index < KuznechikContext::kBlockSize; ++shift_index) {
        // Load elements
        __m128 ans_elements = _mm_loadu_ps((float*)ans.data.data());
        __m128 inverted_linear_transform_matrix_elements = _mm_loadu_ps((float*)inverted_linear_transform_matrix[shift_index][block[shift_index]].data.data());

        // Apply XOR
        __m128 xor_result_elements = _mm_xor_ps(ans_elements, inverted_linear_transform_matrix_elements);

        // Store elements
        _mm_storeu_ps((float*)ans.data.data(), xor_result_elements);
    }

    block = std::move(ans);
#endif // OPTIMIZATION_LEVEL_2
}