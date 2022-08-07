#pragma once

#include "Gradient.hpp"

namespace ImGuiGradient {

// TODO(ASG) RelativePosition should be passed by copy
auto Gradient::get_marks_surrounding(const RelativePosition& position) const -> SurroundingMarks
{
    const Mark* lower{nullptr};
    const Mark* upper{nullptr};
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
    return SurroundingMarks{lower, upper};
}

auto Gradient::compute_color_at(const RelativePosition& position) const -> ColorRGBA
{
    const auto        surrounding_marks = get_marks_surrounding(position);
    const Mark* const lower{surrounding_marks.lower};
    const Mark* const upper{surrounding_marks.upper};

    if (!lower && !upper)
    {
        return ColorRGBA{0.f, 0.f, 0.f, 1.f};
    }
    else if (upper && !lower)
    {
        return upper->color;
    }
    else if (!upper && lower)
    {
        return lower->color;
    }
    else if (upper == lower)
    {
        return upper->color;
    }
    else
    {
        const float mix_factor = (position.get() - lower->position.get()) /
                                 (upper->position.get() - lower->position.get());
        return ImLerp(
            lower->color,
            upper->color,
            mix_factor
        );
    }
};

} // namespace ImGuiGradient
