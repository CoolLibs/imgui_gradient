#pragma once
#include <cmath>

// https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf page 260

// TODO(ASG) Return RelativePositions from these functions.
// TODO(ASG) Put in namespace internal, remove Utils. Because they are included in our public headers.
namespace Utils {

inline auto clamp(float x) -> float
{
    return std::fmin(std::fmax(x, 0.f), 1.f);
}
/// Always returns a number between 0.f and 1.f, even if x is negative.
inline auto fract(float x) -> float
{
    return x - std::floor(x);
}

inline auto modulo(float x, float mod) -> float
{
    return fract(x / mod) * mod;
}

inline auto repeat_position(float position) -> float
{
    return fract(position);
}

// Applies a mirror transform on position given around 0.f, then clamp it between 0.f and 1.f
inline auto mirror_clamp_position(float position) -> float
{
    return clamp(abs(position));
}

// Applies a mirror transform on position given around 0.f, then repeat it
inline auto mirror_repeat_position(float position) -> float
{
    return 1.f - (abs(modulo(position, 2.f) - 1.f));
}

} // namespace Utils