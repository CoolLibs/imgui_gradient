#pragma once

#include <cmath>

namespace utils {

static float repeat_position(float position)
{
    return fmodf(position, 1.f);
}

static float mirror_clamp_position(float position)
{
    return fmodf(abs(position - 1.f), 1.f);
}

static float mirror_repeat_position(float position)
{
    const float Abs    = abs(position);
    const float Floor  = floor(Abs);
    const float Clamp  = fmodf(Floor, 2.f);
    const float Rest   = Abs - Floor;
    const float Mirror = Clamp + Rest;
    return (Mirror >= 1.f) ? Rest : 1.f - Rest;
}

} // namespace utils