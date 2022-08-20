#include "Gradient.hpp"
#include <algorithm>
#include "imgui_internal.hpp"

namespace ImGuiGradient {

Gradient::Gradient(const std::list<ImGuiGradient::Mark>& marks_list)
{
    _marks.clear();
    _marks = marks_list;
}

void Gradient::sort_marks()
{
    _marks.sort([](const Mark& a, const Mark& b) { return a.position < b.position; });
}

auto Gradient::find(MarkId id) const -> const Mark*
{
    return id.find(*this);
}
auto Gradient::find(MarkId id) -> Mark*
{
    return id.find(*this);
}

auto Gradient::add_mark(const Mark& mark) -> MarkId
{
    _marks.push_back(mark);
    auto reference = MarkId{_marks.back()};
    sort_marks();
    return reference;
}

void Gradient::remove_mark(MarkId mark)
{
    const auto* const ptr = find(mark);
    if (ptr)
    {
        _marks.remove(*ptr);
    }
}

auto Gradient::get_marks() const -> const std::list<Mark>&
{
    return _marks;
}

void Gradient::set_mark_position(MarkId const mark, const RelativePosition position)
{
    auto* const ptr = find(mark);
    if (ptr)
    {
        ptr->position = position;
        sort_marks();
    }
}

void Gradient::set_mark_color(const MarkId mark, const ColorRGBA color)
{
    auto* const ptr = find(mark);
    if (ptr)
    {
        ptr->color = color;
    }
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

auto Gradient::at(const RelativePosition position) const -> ColorRGBA
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
