#include "Gradient.hpp"

namespace ImGuiGradient {

auto Gradient::compute_color_at(RelativePosition position) const -> ImVec4
{
    const Mark* lower = nullptr;
    const Mark* upper = nullptr;
    for (const Mark& mark : _marks)
    {
        if (mark.position > position &&
            (!upper || mark.position < upper->position))
        {
            upper = &mark;
        }
        if (mark.position < position &&
            (!lower || mark.position > lower->position))
        {
            lower = &mark;
        }
    }
    if (!lower && !upper)
    {
        return ImVec4{0.f, 0.f, 0.f, 1.f};
    }
    else if (upper && !lower)
    {
        return upper->color;
    }
    else if (!upper && lower)
    {
        return lower->color;
    }

    if (upper == lower)
    {
        return upper->color;
    }
    else
    {
        float mix = (position.get() - lower->position.get()) /
                    (upper->position.get() - lower->position.get());
        return ImLerp(lower->color, upper->color, mix);
    }
};

} // namespace ImGuiGradient
