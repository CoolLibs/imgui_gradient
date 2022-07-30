#pragma once

// https://registry.khronos.org/OpenGL/specs/gl/glspec46.core.pdf p260

#include <imgui/imgui_internal.h>
#include <cmath>

namespace utils {

/// Always returns a number between 0.f and 1.f, even if x is negative.
static auto fract(float x) -> float
{
    return x - std::floor(x);
}

static auto modulo(float x, float y) -> float
{
    return fract(x / y) * y;
}

static auto repeat_position(float position) -> float
{
    return fract(position);
}

static auto mirror_clamp_position(float position) -> float
{
    return ImClamp(abs(position), 0.f, 1.f);
}

static auto mirror_repeat_position(float position) -> float
{
    return 1.f - (abs(modulo(position, 2.f) - 1.f));
}

} // namespace utils