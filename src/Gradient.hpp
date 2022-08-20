#pragma once

#include <algorithm>
#include <iterator>
#include <list>
#include "MarkId.hpp"
#include "SurroundingMarks.hpp"

namespace ImGuiGradient {

class Gradient {
public:
    Gradient() = default;
    explicit Gradient(const std::list<ImGuiGradient::Mark>& mark_list);

    auto at(RelativePosition position) const -> ColorRGBA;

    auto find(MarkId id) const -> const Mark*;
    auto find(MarkId id) -> Mark*;
    auto contains(MarkId id) const -> bool { return find(id); }

    auto add_mark(const Mark& mark) -> MarkId;
    void remove_mark(MarkId mark);
    void set_mark_position(MarkId mark, RelativePosition position);
    void set_mark_color(MarkId mark, ColorRGBA color);

    auto get_marks() const -> const std::list<Mark>&;
    auto is_empty() const -> bool;

    /// Returns the marks positionned just before and after `position`, or nullptr if there is none.
    auto get_marks_surrounding(RelativePosition position) const -> internal::SurroundingMarks;

    friend auto operator==(const Gradient& a, const Gradient& b) -> bool { return a._marks == b._marks; }

private:
    void sort_marks();
    template<typename GradientT>
    friend auto find_impl(GradientT&& gradient, MarkId id)
    {
        const auto it = std::find_if(gradient._marks.begin(), gradient._marks.end(), [&](const Mark& mark) {
            return &mark == id.get_ptr();
        });
        return it != gradient._marks.end()
                   ? &*it
                   : nullptr;
    }

private:
    std::list<Mark> _marks{
        // We use a std::list instead of a std::vector because it doesn't invalidate our iterators when adding, removing or sorting the marks.
        Mark{RelativePosition{0.f}, ImVec4{0.f, 0.f, 0.f, 1.f}},
        Mark{RelativePosition{1.f}, ImVec4{1.f, 1.f, 1.f, 1.f}},
    };
};

} // namespace ImGuiGradient