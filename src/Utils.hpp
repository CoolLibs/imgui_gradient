#pragma once

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#include <imgui/imgui_internal.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include <cmath>

// https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf p260

namespace Utils {

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

// TODO(ASG) Apply the actua wrap mode on textures and see what happens

// Applies a mirror transform on position given around 0.f, then clamp it between 0.f and 1.f
inline auto mirror_clamp_position(float position) -> float
{
    return ImClamp(abs(position), 0.f, 1.f);
}

// Applies a mirror transform on position given around 0.f, then repeat it
inline auto mirror_repeat_position(float position) -> float
{
    return 1.f - (abs(modulo(position, 2.f) - 1.f));
}

} // namespace Utils