#include <random>
#include <chrono>

#include "algorithm.hpp"

int main() {
    KuznechikContext::UserKey user_key = {
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00,
        0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88,
        0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
        0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe
    };

    auto context = KuznechikContext(std::move(user_key));

    // Encrypt sample block
    KuznechikContext::Block sample_block = {
        0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
        0x00, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11
    };

    context.Encrypt(sample_block);
    std::cout << sample_block << std::endl;

    context.Decrypt(sample_block);
    std::cout << sample_block << std::endl;

    ///////////////////////

    const int kRandomSeed = 42;
    std::mt19937 generator(kRandomSeed);
    std::uniform_int_distribution<int> dist(0, 255);

    std::array<KuznechikContext::Block, 6400> test_data;
    for (auto& block : test_data) {
        for (auto& elem : block.data) {
            elem = static_cast<uint8_t>(dist(generator));
        }
    }

    auto start = std::chrono::steady_clock::now();

    int iterations_count = 20;
    for (int i = 0; i < iterations_count; ++i) {
        for (auto& block : test_data) {
            context.Encrypt(block);
            context.Decrypt(block);
        }
    }

    auto end = std::chrono::steady_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    double bytes_per_second = 2.0 * iterations_count * test_data.size() * KuznechikContext::kBlockSize / seconds;

    std::cout << bytes_per_second / 1024 << "Kbytes/sec" << std::endl; // Kbytes per second

    return 0;
}