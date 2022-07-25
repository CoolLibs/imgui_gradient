#pragma once

#include "Gradient.h"
#include "gradient_variables.h"
#include "imgui_draw_utils.h"

namespace ImGuiGradient {

static void draw_border_widget(const ImVec2 vec1, const ImVec2 vec2, ImColor color)
{
    ImDrawList& draw_list = *ImGui::GetWindowDrawList();
    utils::draw_border(draw_list, vec1, vec2, color);
}

static void draw_bar_border(ImDrawList& draw_list, const ImVec2 vec1, const ImVec2 vec2, ImColor color)
{
    const auto margin = ImVec2{2.f, 2.f};
    utils::draw_border(draw_list, vec1 - margin, vec2 + margin, color);
}

static void draw_gradient(ImGuiGradient::Gradient& gradient, ImDrawList& draw_list, const ImVec2& bar_pos, const float bar_bottom, float width)
{
    float current_starting_x = bar_pos.x;
    for (auto markIt = gradient.get_list().begin(); markIt != gradient.get_list().end(); ++markIt)
    {
        ImGuiGradient::Mark& mark = *markIt;

        ImU32 colorBU32 = ImGui::ColorConvertFloat4ToU32(mark.color);
        ImU32 colorAU32 = (markIt != gradient.get_list().begin()) ? ImGui::ColorConvertFloat4ToU32(std::prev(markIt)->color) : colorBU32;

        const float from = current_starting_x;
        const float to   = bar_pos.x + mark.position.get() * width;
        if (mark.position != 0.f)
        {
            utils::draw_gradient_partial(draw_list, ImVec2(from, bar_pos.y), ImVec2(to, bar_bottom), colorAU32, colorBU32);
        }
        current_starting_x = to;
    }

    if (!gradient.get_list().empty() && gradient.get_list().back().position != 1.f)
    // If last element not at the end position extend its color to the end position
    {
        ImU32 colorBU32 = ImGui::ColorConvertFloat4ToU32(gradient.get_list().back().color);
        utils::draw_uniform_square(draw_list, ImVec2(current_starting_x, bar_pos.y), ImVec2(bar_pos.x + width, bar_bottom), colorBU32);
    }
}

static void draw_background_mark(ImDrawList& draw_list, const ImVec2 pos, ImColor border_color, ImColor inside_border_color, const float arrow_border, const float offset)
{
    const float arrow_inside_border = arrow_border - offset;

    const auto arrow_border_x = ImVec2{arrow_border, 0.f};
    const auto arrow_border_y = ImVec2{0.f, arrow_border};

    const auto offset_y = ImVec2{0.f, offset};

    const auto arrow_inside_border_x = ImVec2{arrow_inside_border, 0.f};
    const auto arrow_inside_border_y = ImVec2{0.f, arrow_inside_border};

    utils::draw_triangle(draw_list, pos - arrow_border_y, pos - arrow_border_x, pos + arrow_border_x, border_color);
    utils::draw_uniform_square(draw_list, pos - arrow_border_x, pos + arrow_border_x + ImVec2{0.f, 2.f} * arrow_border_y, border_color);
    utils::draw_uniform_square(draw_list, pos - arrow_inside_border_x + offset_y, pos + arrow_inside_border_x + ImVec2{0.f, 2.f} * arrow_inside_border_y + offset_y, inside_border_color);
}

static void arrow_selected(ImDrawList& draw_list, const ImVec2 pos, ImColor selected_color, const float arrow_inside_border, const float arrow_selected, const float offset)
{
    const auto offset_y = ImVec2{0.f, offset};

    const auto arrow_inside_border_x = ImVec2{arrow_inside_border, 0.f};
    const auto arrow_inside_border_y = ImVec2{0.f, arrow_inside_border};

    const auto arrow_selected_x = ImVec2{arrow_selected, 0.f};
    const auto arrow_selected_y = ImVec2{0.f, arrow_selected};

    utils::draw_triangle(draw_list, pos - arrow_selected_y - offset_y, pos + offset_y - arrow_selected_x, pos + arrow_selected_x + offset_y, selected_color);
    draw_list.AddRect(pos - arrow_inside_border_x + offset_y, pos + arrow_inside_border_x + ImVec2{0.f, 2.f} * arrow_inside_border_y + offset_y, selected_color, 1.0f, ImDrawFlags_Closed);
}

static void mark_button(const ImVec2 vec, const float arrow_border)
{
    ImGui::SetCursorScreenPos(vec - ImVec2{arrow_border, 0.f});
    const ImVec2 button_size = {arrow_border * 2.f, arrow_border * 2.f};
    ImGui::InvisibleButton("mark", button_size);
}

static void draw_mark(ImDrawList& draw_list, const ImVec2 pos, ImColor mark_color, const float arrow_border, bool cond)
{
    const float offset = 1.f;

    ImGuiGradient::draw_background_mark(
        draw_list,
        pos,
        variables::border_color(), variables::inside_arrow_border_color(),
        arrow_border, offset
    );
    if (cond)
    {
        const float arrow_selected      = 4.f;
        const float arrow_inside_border = arrow_border - offset;

        ImGuiGradient::arrow_selected(
            draw_list,
            pos,
            variables::selected_mark_color(),
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

static void mark_button(ImDrawList& draw_list, const ImVec2 pos, ImColor mark_color, bool cond)
{
    const float arrow_border = 6.f;
    draw_mark(draw_list, pos, mark_color, arrow_border, cond);
    ImGuiGradient::mark_button(pos, arrow_border);
}

} // namespace ImGuiGradient