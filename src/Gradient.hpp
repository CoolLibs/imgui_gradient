#pragma once

#include <list>
#include "Mark.hpp"

namespace ImGuiGradient {

// TODO(ASG) put in namespace internal
struct SurroundingMarks {
    /// First mark positionned before `position`, or nullptr if there is none // TODO(ASG) This comment is wrong because I have no idea what "position" is. The comments would make more sense if they were around get_marks_surrounding()
    const Mark* lower{nullptr};
    /// First mark positionned after `position`, or nullptr if there is none // TODO(ASG) same
    const Mark* upper{nullptr};
};

class Gradient {
public:
    auto get_marks_surrounding(const RelativePosition& position) const -> SurroundingMarks;
    auto compute_color_at(const RelativePosition& position) const -> ColorRGBA;

    // TODO(ASG) Move all function implementations to the .cpp
    auto add_mark(const Mark& mark) -> Mark&
    {
        _marks.push_back(mark);
        Mark* ptr = &_marks.back(); // TODO(ASG) Why not store a reference directly ?
        sort_marks();
        return *ptr;
    };

    void remove_mark(const Mark& mark)
    {
        _marks.remove(mark);
        sort_marks(); // TODO(ASG) I think that sorting is useless here because removing a mark preserves the relative order of the other marks
    };

    void set_mark_position(Mark& mark, const RelativePosition position)
    {
        mark.position.set(position.get());
        sort_marks();
    };

    void set_mark_color(Mark& mark, const ColorRGBA color) // TODO(ASG) Warning from clang-tidy: "method 'set_mark_color' can be made static (clang-tidy(readability-convert-member-functions-to-static))"
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
    std::list<Mark> _marks{
        // We use a std::list instead of a std::vector because it doesn't invalidate our iterators when adding, removing or sorting the marks.
        Mark{RelativePosition{0.f}, ImVec4{0.f, 0.f, 0.f, 1.f}},
        Mark{RelativePosition{1.f}, ImVec4{1.f, 1.f, 1.f, 1.f}},
    };
};

} // namespace ImGuiGradient