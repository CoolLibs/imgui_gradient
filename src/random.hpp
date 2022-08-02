#pragma once

#include <random>

namespace utils {

static float rand(std::default_random_engine& generator)
{
    std::uniform_real_distribution<float> distribution{0.f, 1.f};
    return distribution(generator);
}

} // namespace utils