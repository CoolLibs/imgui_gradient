#pragma once

#include <random>

namespace Utils {

// TODO(ASG) Move directly in Gradient.cpp as a static function and remove the Utils namespace
inline auto random(std::default_random_engine& generator) -> float
{
    return std::uniform_real_distribution<float>{0.f, 1.f}(generator);
}

} // namespace Utils