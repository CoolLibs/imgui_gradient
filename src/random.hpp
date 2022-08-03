#pragma once

#include <random>

namespace Utils {

inline auto random(std::default_random_engine& generator) -> float
{
    const auto distribution = std::uniform_real_distribution<float>{0.f, 1.f};
    return distribution(generator);
}

} // namespace Utils