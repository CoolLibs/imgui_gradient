#pragma once
#include "Gradient.hpp"

namespace ImGuiGradient {

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
    SurroundingMarks surrounding_marks{};
    surrounding_marks.lower = lower;
    surrounding_marks.upper = upper;
    return surrounding_marks;
}

auto Gradient::compute_color_at(const RelativePosition& position) const -> ColorRGBA
{
    SurroundingMarks surrounding_marks = get_marks_surrounding(position);
    if (!surrounding_marks.lower && !surrounding_marks.upper)
    {
        return ColorRGBA{0.f, 0.f, 0.f, 1.f};
    }
    else if (surrounding_marks.upper && !surrounding_marks.lower)
    {
        return surrounding_marks.upper->color;
    }
    else if (!surrounding_marks.upper && surrounding_marks.lower)
    {
        return surrounding_marks.lower->color;
    }

    if (surrounding_marks.upper == surrounding_marks.lower)
    {
        return surrounding_marks.upper->color;
    }
    else
    {
        const float mix_factor = (position.get() - surrounding_marks.lower->position.get()) /
                                 (surrounding_marks.upper->position.get() - surrounding_marks.lower->position.get());
        return ImLerp(surrounding_marks.lower->color, surrounding_marks.upper->color, mix_factor);
    }
};

} // namespace ImGuiGradient
