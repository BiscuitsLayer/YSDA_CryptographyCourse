#include "galois_field.hpp"

void GaloisField::GenerateMultiplicationResults() {
    for (size_t left_value = 0; left_value < GaloisField::kOrderValue; ++left_value) {
        for (size_t right_value = 0; right_value < GaloisField::kOrderValue; ++right_value) {
            GaloisField::Element lhs{static_cast<uint8_t>(left_value)};
            GaloisField::Element rhs{static_cast<uint8_t>(right_value)};

            multiplication_results[left_value][right_value] = static_cast<uint8_t>(lhs * rhs);
        }
    }
}

GaloisField::Element GaloisField::Element::operator*(GaloisField::Element other) {
    Element ans;
    if ((primitive_power_ == kInv) || (other.primitive_power_ == kInv)) {
        ans.primitive_power_ = kInv;
    } else {
        ans.primitive_power_ = (primitive_power_ + other.primitive_power_) % GaloisField::kModuloValue;
    }
    return ans;
}

std::ostream& operator<<(std::ostream& stream, const GaloisField::Element element) {
    stream << static_cast<int>(GaloisField::primitive_power_to_number[element.primitive_power_]);
    return stream;
}