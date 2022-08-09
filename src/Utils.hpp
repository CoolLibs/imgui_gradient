#pragma once

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#define IMGUI_DEFINE_MATH_OPERATORS // Need ImVec operators in other files but we have to include imgui_internal there, // TODO(ASG) That comment is a lie, we don't need imgui_internal here at all!
                                    // therefore to include imgui_internal in the library with these operators we have to define it there
#include <imgui/imgui_internal.h>   // include ImClamp
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include <cmath>

// https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf page 260

// TODO(ASG) Return RelativePositions from these functions.
// TODO(ASG) Put in namespace internal, remove Utils. Because they are included in our public headers.
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