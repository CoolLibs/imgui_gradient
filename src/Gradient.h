#pragma once

#include "Marks.h"
#include "PositionMode.h"

namespace ImGuiGradient {

class Gradient {
public:
    Gradient();
    ImVec4 get_color_at(float position, PositionMode mode) const;
    Mark*  add_mark(const Mark& mark)
    {
        return m_marks.add_mark(mark);
    };
    void remove_mark(const Mark& mark)
    {
        m_marks.remove_mark(mark);
    };
    void reset();
    Mark next_mark(Mark* mark) { return m_marks.next_mark(mark); };         // Be carefull do not use if there is no next mark
    Mark previous_mark(Mark* mark) { return m_marks.previous_mark(mark); }; // Be carefull do not use if there is no previous mark
    auto is_empty() -> bool
    {
        return m_marks.m_list.empty();
    }
    std::list<Mark>& get_list() { return m_marks.m_list; }
    Marks&           get_marks() { return m_marks; }

    friend auto operator==(const Gradient& a, const Gradient& b) -> bool { return a.m_marks.m_list == b.m_marks.m_list; }

private:
    ImVec4 compute_color_at(RelativePosition position) const;
    Marks  m_marks{};
};

} // namespace ImGuiGradient