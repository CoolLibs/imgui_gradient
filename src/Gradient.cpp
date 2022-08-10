#pragma once

#include "Gradient.hpp"
#include <imgui/imgui_internal.h>

// TODO(ASG) Fix builds on all platforms (see CI in GitHub Actions https://github.com/CoolLibs/imgui_gradient/actions)

namespace ImGuiGradient {

void Gradient::sort_marks()
{
    _marks.sort([](const Mark& a, const Mark& b) { return a.position < b.position; });
}

auto Gradient::add_mark(const Mark& mark) -> Mark&
{
    _marks.push_back(mark);
    Mark& reference = _marks.back();
    sort_marks();
    return reference;
}

void Gradient::remove_mark(const Mark& mark)
{
    _marks.remove(mark);
}

auto Gradient::get_marks() const -> const std::list<Mark>&
{
    return _marks;
}

void Gradient::set_mark_position(const Mark& mark, const RelativePosition position)
{
    const_cast<Mark&>(mark).position.set(position.get());
    sort_marks();
}

void Gradient::set_mark_color(const Mark& mark, const ColorRGBA color)
{
    const_cast<Mark&>(mark).color = color;
}

auto Gradient::is_empty() const -> bool
{
    return _marks.empty();
}

auto Gradient::get_marks_surrounding(const RelativePosition position) const -> internal::SurroundingMarks
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
    return internal::SurroundingMarks{lower, upper};
}

auto Gradient::compute_color_at(const RelativePosition position) const -> ColorRGBA
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
