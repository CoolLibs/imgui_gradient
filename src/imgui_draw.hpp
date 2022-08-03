#pragma once

#include "Gradient.hpp"
#include "Interpolation.hpp"
#include "gradient_variables.hpp"
#include "imgui_draw_utils.hpp"

namespace ImGuiGradient {

static void draw_border_widget(const ImVec2 vec1, const ImVec2 vec2, ImColor color)
{
    ImDrawList& draw_list = *ImGui::GetWindowDrawList();
    utils::draw_border(draw_list, vec1, vec2, color);
}

static void draw_gradient_border(ImDrawList& draw_list, const ImVec2 vec1, const ImVec2 vec2, ImColor color)
{
    const auto margin = ImVec2{2.f, 2.f};
    utils::draw_border(draw_list, vec1 - margin, vec2 + margin, color);
}

static void draw_gradient(Gradient& gradient, ImDrawList& draw_list, const Interpolation& interpolation_mode, const ImVec2& gradient_bar_pos, const float gradient_bar_bottom, float width)
{
    float current_starting_x = gradient_bar_pos.x;
    for (auto markIt = gradient.get_marks().begin(); markIt != gradient.get_marks().end(); ++markIt)
    {
        const Mark& mark = *markIt;

        ImU32 colorBU32 = ImGui::ColorConvertFloat4ToU32(mark.color);
        ImU32 colorAU32 = (markIt != gradient.get_marks().begin()) ? ImGui::ColorConvertFloat4ToU32(std::prev(markIt)->color) : colorBU32;

        const float from = current_starting_x;
        const float to   = gradient_bar_pos.x + mark.position.get() * (width);
        if (mark.position != 0.f)
        {
            if (interpolation_mode == Interpolation::Linear)
            {
                utils::draw_gradient_between_two_colors(draw_list, ImVec2(from, gradient_bar_pos.y), ImVec2(to, gradient_bar_bottom), colorAU32, colorBU32);
            }
            else
            {
                utils::draw_uniform_square(draw_list, ImVec2(from, gradient_bar_pos.y), ImVec2(to, gradient_bar_bottom), colorBU32);
            }
        }
        current_starting_x = to;
    }
    // If last element not at the end position extend its color to the end position
    if (gradient.get_marks().back().position != 1.f)
    {
        ImU32 colorBU32 = ImGui::ColorConvertFloat4ToU32(gradient.get_marks().back().color);
        utils::draw_uniform_square(draw_list, ImVec2(current_starting_x, gradient_bar_pos.y), ImVec2(gradient_bar_pos.x + width, gradient_bar_bottom), colorBU32);
    }
}

static void draw_background_mark(ImDrawList& draw_list, const ImVec2 pos, ImColor arrow_mark, const float arrow_border, const float offset)
{
    const float arrow_inside_border = arrow_border - offset;

    const auto arrow_border_x = ImVec2{arrow_border, 0.f};
    const auto arrow_border_y = ImVec2{0.f, arrow_border};

    const auto offset_y = ImVec2{0.f, offset};

    const auto arrow_inside_border_x = ImVec2{arrow_inside_border, 0.f};
    const auto arrow_inside_border_y = ImVec2{0.f, arrow_inside_border};

    draw_list.AddTriangleFilled(pos - arrow_border_y, pos - arrow_border_x, pos + arrow_border_x, arrow_mark);
    utils::draw_uniform_square(draw_list, pos - arrow_border_x, pos + arrow_border_x + ImVec2{0.f, 2.f} * arrow_border_y, arrow_mark);
    utils::draw_uniform_square(draw_list, pos - arrow_inside_border_x + offset_y, pos + arrow_inside_border_x + ImVec2{0.f, 2.f} * arrow_inside_border_y + offset_y, arrow_mark);
}

static void arrow_selected(ImDrawList& draw_list, const ImVec2 pos, ImColor selected_color, const float arrow_inside_border, const float arrow_selected, const float offset)
{
    const auto offset_y = ImVec2{0.f, offset};

    const auto arrow_inside_border_x = ImVec2{arrow_inside_border, 0.f};
    const auto arrow_inside_border_y = ImVec2{0.f, arrow_inside_border};

    const auto arrow_selected_x = ImVec2{arrow_selected, 0.f};
    const auto arrow_selected_y = ImVec2{0.f, arrow_selected};

    draw_list.AddTriangleFilled(pos - arrow_selected_y - offset_y, pos + offset_y - arrow_selected_x, pos + arrow_selected_x + offset_y, selected_color);
    draw_list.AddRect(pos - arrow_inside_border_x + offset_y, pos + arrow_inside_border_x + ImVec2{0.f, 2.f} * arrow_inside_border_y + offset_y, selected_color, 1.0f, ImDrawFlags_Closed);
}

static bool mark_invisible_button(const ImVec2 vec, const float arrow_border)
{
    ImGui::SetCursorScreenPos(vec - ImVec2{arrow_border * 1.5f, settings.gradient_editor_height});
    const ImVec2 button_size = {arrow_border * 3.f, settings.gradient_editor_height + arrow_border * 2.f};
    ImGui::InvisibleButton("mark", button_size);
    return ImGui::IsItemHovered();
}

static void draw_mark(ImDrawList& draw_list, const ImVec2 pos, ImColor background_mark_color, ImColor mark_color, const float arrow_border, bool cond)
{
    const float offset = 1.f;

    ImGuiGradient::draw_background_mark(
        draw_list,
        pos,
        background_mark_color,
        arrow_border, offset
    );
    if (cond)
    {
        const float arrow_selected      = 4.f;
        const float arrow_inside_border = arrow_border - offset;

        ImGuiGradient::arrow_selected(
            draw_list,
            pos,
            internal::color__selected_mark(),
            arrow_inside_border, arrow_selected, offset
        );
    }

    const auto square_height   = 3.f;
    const auto square_height_x = ImVec2{square_height, 0.f};
    const auto square_height_y = ImVec2{0.f, square_height};
    utils::draw_uniform_square(
        draw_list,
        pos - square_height_x + square_height_y,
        pos + square_height_x + square_height_y * square_height_y,
        mark_color
    );
}

static void mark_invisble_hitbox(ImDrawList& draw_list, const ImVec2 pos, ImColor mark_color, bool cond)
{
    const float arrow_border = 6.f;
    draw_mark(
        draw_list,
        pos,
        mark_invisible_button(pos, arrow_border) ? internal::color__hovered_mark()
                                                 : internal::color__mark(),
        mark_color,
        arrow_border,
        cond
    );
}

} // namespace ImGuiGradient