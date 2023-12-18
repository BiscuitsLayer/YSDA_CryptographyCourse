#include "context.hpp"
#include "linear_transform.hpp"
#include "feistel_network.hpp"

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
        round_constant[0] = counter++;
        LinearTransform::Forward(round_constant);
    }
}

void KuznechikContext::GenerateRoundKeys(UserKey&& user_key) {
    // First two keys are two halves of the user key
    std::move(user_key.begin(), user_key.begin() + kBlockSize, round_keys[0].data.begin());
    std::move(user_key.begin() + kBlockSize, user_key.end(), round_keys[1].data.begin());

    FeistelNetwork::Forward();
}