#pragma once

#include <list>
#include "Interpolation.hpp"
#include "MarkId.hpp"

namespace ImGG {

class Gradient {
public:
    Gradient() = default;
    explicit Gradient(const std::list<Mark>& marks)
        : _marks{marks}
    {}

    /// Returns the color at the given position in the gradient.
    /// 0.f corresponds to the beginning of the gradient and 1.f to the end.
    auto at(RelativePosition, Interpolation = Interpolation::Linear) const -> ColorRGBA;

    auto find(MarkId) const -> const Mark*;
    auto find(MarkId) -> Mark*;
    auto contains(MarkId id) const -> bool { return find(id); }
    auto is_empty() const -> bool;

    auto add_mark(const Mark&) -> MarkId;
    void remove_mark(MarkId);
    void set_mark_position(MarkId, RelativePosition);
    void set_mark_color(MarkId, ColorRGBA);

    auto get_marks() const -> const std::list<Mark>&;

    friend auto operator==(const Gradient& a, const Gradient& b) -> bool { return a._marks == b._marks; }

private:
    void sort_marks();

private:
    std::list<Mark> _marks{
        // We use a std::list instead of a std::vector because it doesn't invalidate our iterators when adding, removing or sorting the marks.
        Mark{RelativePosition{0.f}, ColorRGBA{0.f, 0.f, 0.f, 1.f}},
        Mark{RelativePosition{1.f}, ColorRGBA{1.f, 1.f, 1.f, 1.f}},
    };

    friend class MarkId;
};

} // namespace ImGG