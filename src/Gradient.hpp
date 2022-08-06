#pragma once

#include <list>
#include "Mark.hpp"

namespace ImGuiGradient {

using RGBAColor = ImVec4; // TODO(ASG) Remove this one

class Gradient {
public:
    auto compute_color_at(RelativePosition position) const -> ColorRGBA;

    auto add_mark(const Mark& mark) -> Mark&
    {
        _marks.push_back(mark);
        Mark* ptr = &_marks.back();
        sort_marks();
        return *ptr;
    };
    void remove_mark(const Mark& mark)
    {
        _marks.remove(mark);
        sort_marks();
    };
    void set_mark_position(Mark& mark, const RelativePosition position)
    {
        mark.position.set(position.get());
        sort_marks();
    };
    void set_mark_color(Mark& mark, const RGBAColor color)
    {
        mark.color = color;
    };

    auto is_empty() -> bool
    {
        return _marks.empty();
    }
    auto get_marks() const -> const std::list<Mark>& { return _marks; }

    friend auto operator==(const Gradient& a, const Gradient& b) -> bool { return a._marks == b._marks; }

private:
    void sort_marks()
    {
        _marks.sort([](const Mark& a, const Mark& b) { return a.position < b.position; });
    }

private:
    // Use std::list instead of vector because it is easier to remove a mark when we do not know the index
    std::list<Mark> _marks{
        Mark{RelativePosition{0.f}, ImVec4{0.f, 0.f, 0.f, 1.f}},
        Mark{RelativePosition{1.f}, ImVec4{1.f, 1.f, 1.f, 1.f}}};
};

} // namespace ImGuiGradient