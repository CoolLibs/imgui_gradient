#pragma once

#include "Gradient.hpp"
#include "Interpolation.hpp"
#include "Settings.hpp"
#include "internal.hpp"

namespace ImGG {

inline void draw_border(
    ImDrawList& draw_list,
    ImVec2      top_left_corner,
    ImVec2      bottom_rigth_corner
)
{
    static constexpr float rounding{1.f};
    static constexpr float thickness{2.f};
    draw_list.AddRect(top_left_corner, bottom_rigth_corner, internal::border_color(), rounding, ImDrawFlags_None, thickness);
}

void draw_gradient(
    ImDrawList&     draw_list,
    const Gradient& gradient,
    ImVec2          gradient_position,
    ImVec2          size // {width, height}
);

void draw_marks(
    ImDrawList& draw_list,
    ImVec2      mark_position,
    ImU32       mark_color,
    float       gradient_height,
    bool        mark_is_selected
);

} // namespace ImGG