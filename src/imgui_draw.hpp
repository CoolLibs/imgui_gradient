#pragma once

#include "Gradient.hpp"
#include "Interpolation.hpp"
#include "Settings.hpp"
#include "internal.hpp"

namespace ImGuiGradient {

inline void draw_border(
    ImDrawList&  draw_list,
    const ImVec2 top_left_corner,
    const ImVec2 bottom_rigth_corner
)
{
    static constexpr float rounding{1.f};
    static constexpr float thickness{2.f};
    draw_list.AddRect(top_left_corner, bottom_rigth_corner, internal::border_color(), rounding, ImDrawFlags_None, thickness);
}

void draw_gradient(
    ImDrawList&   draw_list,
    Gradient&     gradient,
    Interpolation interpolation_mode,
    ImVec2        gradient_position,
    ImVec2        size // {width, height}
);

void draw_mark(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const ImU32& mark_color,
    bool         mark_is_selected
);

} // namespace ImGuiGradient