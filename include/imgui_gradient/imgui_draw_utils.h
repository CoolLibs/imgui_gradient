#pragma once

#include <imgui/imgui.h>

namespace utils {

static void draw_uniform_square(ImDrawList& draw_list, const ImVec2 vec1, const ImVec2 vec2, ImColor color)
{
    draw_list.AddRectFilled(vec1, vec2, color, 1.0f, ImDrawFlags_Closed);
}

static void draw_gradient_partial(ImDrawList& draw_list, const ImVec2 vec1, const ImVec2 vec2, ImColor colorA, ImColor colorB)
{
    draw_list.AddRectFilledMultiColor(vec1, vec2, colorA, colorB, colorB, colorA);
}

static void draw_triangle(ImDrawList& draw_list, const ImVec2 vec_triangle_up, const ImVec2 vec_triangle_down_left, const ImVec2 vec_triangle_down_right, ImColor color)
{
    draw_list.AddTriangleFilled(vec_triangle_up, vec_triangle_down_left, vec_triangle_down_right, color);
}

} // namespace utils