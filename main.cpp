#include "algorithm.hpp"

int main() {
    KuznechikContext::GenerateRoundConstants();
    for (auto& round_constant : KuznechikContext::round_constants) {
        std::cout << round_constant << std::endl;
    }
    return 0;
}