#pragma once

#include "context.hpp"

class FeistelNetwork {
public:
    static constexpr size_t kRoundsCount = 8;

    static void Forward();
};