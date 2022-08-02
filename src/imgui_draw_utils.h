#pragma once

#include <imgui/imgui.h>

namespace utils {

inline void draw_border(ImDrawList& draw_list, const ImVec2 top_left_corner, const ImVec2 bottom_rigth_corner, ImColor color)
{
    static constexpr float rounding  = 1.f;
    static constexpr float thickness = 2.f;
    draw_list.AddRect(top_left_corner, bottom_rigth_corner, color, rounding, ImDrawFlags_None, thickness);
}

inline void draw_uniform_square(ImDrawList& draw_list, const ImVec2 top_left_corner, const ImVec2 bottom_rigth_corner, ImColor color)
{
    static constexpr float rounding = 1.f;
    draw_list.AddRectFilled(top_left_corner, bottom_rigth_corner, color, rounding, ImDrawFlags_Closed);
}

inline void draw_gradient_between_two_colors(ImDrawList& draw_list, const ImVec2 top_left_corner, const ImVec2 bottom_rigth_corner, ImColor colorA, ImColor colorB)
{
    draw_list.AddRectFilledMultiColor(top_left_corner, bottom_rigth_corner, colorA, colorB, colorB, colorA);
}

} // namespace utils