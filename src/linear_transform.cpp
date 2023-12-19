#include "linear_transform.hpp"

void LinearTransform::Forward(KuznechikContext::Block& block) {
    uint8_t result = 0;

    for (size_t shift_index = 0; shift_index < KuznechikContext::kBlockSize; ++shift_index) {
        for (size_t coef_index = 0; coef_index < LinearTransform::coefficients.size(); ++coef_index) { 

            size_t byte_index = (coef_index + shift_index) % KuznechikContext::kBlockSize;
            GaloisField::Element byte{block[byte_index]};
            GaloisField::Element coef{LinearTransform::coefficients[coef_index]};

            result ^= static_cast<uint8_t>(coef * byte);
        }

        block[shift_index] = result;
        result = 0;
    }
}

void LinearTransform::Backward(KuznechikContext::Block& block) {
    uint8_t result = 0;

    for (size_t shift_index = KuznechikContext::kBlockSize - 1; shift_index + 1 > 0 ; --shift_index) {
        for (size_t coef_index = 0; coef_index < LinearTransform::coefficients.size(); ++coef_index) { 

            size_t byte_index = (coef_index + shift_index + 1) % KuznechikContext::kBlockSize;
            GaloisField::Element byte{block[byte_index]};
            GaloisField::Element coef{LinearTransform::coefficients[KuznechikContext::kBlockSize - coef_index - 1]};

            result ^= static_cast<uint8_t>(coef * byte);
        }

        block[shift_index] = result;
        result = 0;
    }
}