#pragma once

#include "Mark.hpp"
#include "PositionMode.hpp"

namespace ImGuiGradient {

class Gradient {
public:
    auto compute_color_at(float position, PositionMode mode) const -> ImVec4;
    auto compute_color_at(RelativePosition position) const -> ImVec4;

    void sort_marks()
    {
        _marks.sort([](const Mark& a, const Mark& b) { return a.position < b.position; });
    }
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
    auto is_empty() -> bool
    {
        return _marks.empty();
    }
    // Need a mutable one because in some loops we use it to implement no-const variables
    auto get_marks() -> std::list<Mark>& { return _marks; }
    auto get_marks() const -> const std::list<Mark>& { return _marks; }

    friend auto operator==(const Gradient& a, const Gradient& b) -> bool { return a._marks == b._marks; }

private:
    // Use std::list instead of vector because it is easier to remove a mark when we do not know the index
    std::list<Mark> _marks{Mark{0.f, ImVec4{0.f, 0.f, 0.f, 1.f}}, Mark{1.f, ImVec4{1.f, 1.f, 1.f, 1.f}}};
};

} // namespace ImGuiGradient