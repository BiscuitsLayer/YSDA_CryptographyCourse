#include "galois_field.hpp"

GaloisField::Element GaloisField::Element::operator*(const GaloisField::Element other) {
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