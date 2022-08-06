#pragma once

#include "Gradient.hpp"
#include "Interpolation.hpp"
#include "gradient_settings.hpp"

namespace ImGuiGradient {

inline void draw_border(
    ImDrawList&  draw_list,
    const ImVec2 top_left_corner,
    const ImVec2 bottom_rigth_corner,
    ImColor      color
)
{
    static constexpr float rounding  = 1.f;
    static constexpr float thickness = 2.f;
    draw_list.AddRect(top_left_corner, bottom_rigth_corner, color, rounding, ImDrawFlags_None, thickness);
}

void draw_gradient(
    Gradient&            gradient,
    ImDrawList&          draw_list,
    const Interpolation& interpolation_mode,
    const ImVec2         gradient_bar_pos,
    float                gradient_bar_bottom,
    float                width
);

void mark_invisble_hitbox(
    ImDrawList&  draw_list,
    const ImVec2 pos,
    ImColor      mark_color,
    float        gradient_editor_height,
    bool         mark_is_selected
);

} // namespace ImGuiGradient