#include "context.hpp"
#include "linear_transform.hpp"

bool KuznechikContext::Block::operator==(const Block& other) const {
    for (size_t index = 0; index < kBlockSize; ++index) {
        if (data[index] != other.data[index]) {
            return false;
        }
    }
    return true;
}

void KuznechikContext::GenerateRoundConstants() {
    int counter = 1;

    for (auto& round_constant : round_constants) {
        Block init;
        init[0] = counter++;
        round_constant = LinearTransform::Forward(init);
    }
}

std::ostream& operator<<(std::ostream& stream, const KuznechikContext::Block& block) {
    stream << '{';
    for (size_t index = 0; index < KuznechikContext::kBlockSize; ++index) {
        stream << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(block[index]);
        if (index != KuznechikContext::kBlockSize - 1) {
            stream << ", ";
        } else {
            stream << '}';
        }
    }

    return stream;
}