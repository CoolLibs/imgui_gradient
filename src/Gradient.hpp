#pragma once

#include <list>
#include "SurroundingMarks.hpp"

namespace ImGuiGradient {

class Gradient {
public:
    auto get_marks_surrounding(RelativePosition position) const -> internal::SurroundingMarks;
    auto compute_color_at(RelativePosition position) const -> ColorRGBA;

    auto add_mark(const Mark& mark) -> Mark&;
    void remove_mark(const Mark& mark);
    auto is_empty() -> bool;

    auto get_marks() const -> const std::list<Mark>&;

    void set_mark_position(const Mark& mark, const RelativePosition position);
    void set_mark_color(const Mark& mark, const ColorRGBA color);

    friend auto operator==(const Gradient& a, const Gradient& b) -> bool { return a._marks == b._marks; }

private:
    void sort_marks();

private:
    std::list<Mark> _marks{
        // We use a std::list instead of a std::vector because it doesn't invalidate our iterators when adding, removing or sorting the marks.
        Mark{RelativePosition{0.f}, ImVec4{0.f, 0.f, 0.f, 1.f}},
        Mark{RelativePosition{1.f}, ImVec4{1.f, 1.f, 1.f, 1.f}},
    };
};

} // namespace ImGuiGradient