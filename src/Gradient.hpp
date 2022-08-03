#pragma once

#include "Marks.hpp"
#include "PositionMode.hpp"

namespace ImGuiGradient {

class Gradient {
public:
    ImVec4 compute_color_at(float position, PositionMode mode) const;
    ImVec4 compute_color_at(RelativePosition position) const;

    Mark& add_mark(const Mark& mark)
    {
        return m_marks.add_mark(mark);
    };
    void remove_mark(const Mark& mark)
    {
        m_marks.remove_mark(mark);
    };
    auto is_empty() -> bool
    {
        return m_marks.m_list.empty();
    }
    std::list<Mark>& get_list() { return m_marks.m_list; } // TODO(ASG) Is the mutable ref necessary? const?
    Marks&           get_marks() { return m_marks; }       // TODO(ASG) Only one of the two is necessary, and const& is probably enough

    friend auto operator==(const Gradient& a, const Gradient& b) -> bool { return a.m_marks.m_list == b.m_marks.m_list; }

private:
    Marks m_marks{}; // TODO(ASG) Merge Marks into this class
};

} // namespace ImGuiGradient