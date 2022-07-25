#pragma once

#include <random>

namespace utils {

static float rand() // TODO(ASG) the user could choose the generator
{
    static std::default_random_engine     generator{std::random_device{}()};
    std::uniform_real_distribution<float> distribution{0.f, 1.f};
    return distribution(generator);
}

} // namespace utils