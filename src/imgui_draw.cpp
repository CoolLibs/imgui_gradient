#pragma once

#include "Gradient.hpp"
#include "Interpolation.hpp"
#include "Settings.hpp"
#include "internal.hpp"

namespace ImGuiGradient {

static void draw_uniform_square(
    ImDrawList&  draw_list,
    const ImVec2 top_left_corner,
    const ImVec2 bottom_rigth_corner,
    const ImU32& color
)
{
    static constexpr float rounding = 1.f;
    draw_list.AddRectFilled(
        top_left_corner,
        bottom_rigth_corner,
        color,
        rounding, ImDrawFlags_Closed
    );
}

static void draw_gradient_between_two_colors(
    ImDrawList&  draw_list,
    const ImVec2 top_left_corner,
    const ImVec2 bottom_rigth_corner,
    const ImU32& color_left, const ImU32& color_right
)
{
    draw_list.AddRectFilledMultiColor(
        top_left_corner,
        bottom_rigth_corner,
        color_left, color_right, color_right, color_left
    );
}

void draw_gradient(
    Gradient&           gradient,
    ImDrawList&         draw_list,
    const Interpolation interpolation_mode,
    const ImVec2        gradient_pos,
    const ImVec2        size
)
{
    float current_starting_x = gradient_pos.x;
    for (auto mark_iterator = gradient.get_marks().begin(); mark_iterator != gradient.get_marks().end(); ++mark_iterator)
    {
        const Mark& mark = *mark_iterator;

        const ImU32 color_right = ImGui::ColorConvertFloat4ToU32(mark.color);

        const float from = current_starting_x;
        const float to   = gradient_pos.x + mark.position.get() * (size.x);
        if (mark.position.get() != 0.f)
        {
            if (interpolation_mode == Interpolation::Linear)
            {
                const ImU32 color_left = (mark_iterator != gradient.get_marks().begin())
                                             ? ImGui::ColorConvertFloat4ToU32(std::prev(mark_iterator)->color)
                                             : color_right;
                draw_gradient_between_two_colors(
                    draw_list,
                    ImVec2(from, gradient_pos.y),
                    ImVec2(to, gradient_pos.y + size.y),
                    color_left, color_right
                );
            }
            else
            {
                draw_uniform_square(
                    draw_list,
                    ImVec2(from, gradient_pos.y),
                    ImVec2(to, gradient_pos.y + size.y),
                    color_right
                );
            }
        }
        current_starting_x = to;
    }
    // If last element not at the end position extend its color to the end position
    if (gradient.get_marks().back().position.get() != 1.f)
    {
        draw_uniform_square(
            draw_list,
            ImVec2(current_starting_x, gradient_pos.y),
            ImVec2(gradient_pos.x + size.x, gradient_pos.y + size.y),
            ImGui::ColorConvertFloat4ToU32(gradient.get_marks().back().color)
        );
    }
}

static void draw_background_mark(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const ImU32& arrow_mark_color,
    const float  mark_horizontal_size,
    const float  offset
)
{
    const float arrow_inside_border = mark_horizontal_size - offset;

    const auto mark_horizontal_size_x = ImVec2{mark_horizontal_size, 0.f};
    const auto mark_horizontal_size_y = ImVec2{0.f, mark_horizontal_size};

    const auto offset_y = ImVec2{0.f, offset};

    const auto arrow_inside_border_x = ImVec2{arrow_inside_border, 0.f};
    const auto arrow_inside_border_y = ImVec2{0.f, arrow_inside_border};

    draw_list.AddTriangleFilled(
        mark_position - mark_horizontal_size_y,
        mark_position - mark_horizontal_size_x,
        mark_position + mark_horizontal_size_x,
        arrow_mark_color
    );
    draw_uniform_square(
        draw_list,
        mark_position - mark_horizontal_size_x,
        mark_position + mark_horizontal_size_x + ImVec2{0.f, 2.f} * mark_horizontal_size_y,
        arrow_mark_color
    );
    draw_uniform_square(
        draw_list,
        mark_position - arrow_inside_border_x + offset_y,
        mark_position + arrow_inside_border_x + ImVec2{0.f, 2.f} * arrow_inside_border_y + offset_y,
        arrow_mark_color
    );
}

static void draw_arrow_selected(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const ImU32& selected_color,
    const float  arrow_inside_border,
    const float  arrow_selected_horizontal_size,
    const float  offset
)
{
    const auto offset_y = ImVec2{0.f, offset};

    const auto arrow_inside_border_x = ImVec2{arrow_inside_border, 0.f};
    const auto arrow_inside_border_y = ImVec2{0.f, arrow_inside_border};

    const auto arrow_selected_horizontal_size_x = ImVec2{arrow_selected_horizontal_size, 0.f};
    const auto arrow_selected_horizontal_size_y = ImVec2{0.f, arrow_selected_horizontal_size};

    draw_list.AddTriangleFilled(
        mark_position - arrow_selected_horizontal_size_y - offset_y,
        mark_position + offset_y - arrow_selected_horizontal_size_x, mark_position + arrow_selected_horizontal_size_x + offset_y,
        selected_color
    );
    draw_list.AddRect(
        mark_position - arrow_inside_border_x + offset_y,
        mark_position + arrow_inside_border_x + ImVec2{0.f, 2.f} * arrow_inside_border_y + offset_y,
        selected_color,
        1.0f,
        ImDrawFlags_Closed
    );
}

static void draw_mark(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const ImU32& background_mark_color,
    const ImU32& mark_color,
    float        mark_horizontal_size,
    bool         mark_is_selected
)
{
    static constexpr auto offset{1.f};

    draw_background_mark(
        draw_list,
        mark_position,
        background_mark_color,
        mark_horizontal_size, offset
    );
    if (mark_is_selected)
    {
        const float arrow_selected_horizontal_size = 4.f;
        const float arrow_inside_border            = mark_horizontal_size - offset;

        draw_arrow_selected(
            draw_list,
            mark_position,
            internal::selected_mark_color(),
            arrow_inside_border, arrow_selected_horizontal_size, offset
        );
    }

    const auto square_height   = 3.f;
    const auto square_height_x = ImVec2{square_height, 0.f};
    const auto square_height_y = ImVec2{0.f, square_height};
    draw_uniform_square(
        draw_list,
        mark_position - square_height_x + square_height_y,
        mark_position + square_height_x + square_height_y * square_height_y,
        mark_color
    );
}

static auto mark_invisible_button(
    const ImVec2 vec,
    const float  mark_horizontal_size
) -> bool
{
    ImGui::SetCursorScreenPos(vec - ImVec2{mark_horizontal_size * 1.5f, 0.f});
    const auto button_size = ImVec2{mark_horizontal_size * 3.f, mark_horizontal_size * 2.f};
    ImGui::InvisibleButton("mark", button_size);
    return ImGui::IsItemHovered();
}

static auto mark_drawing_color(
    const ImVec2 mark_position,
    const float  mark_horizontal_size
) -> ImU32
{
    return mark_invisible_button(mark_position, mark_horizontal_size)
               ? internal::hovered_mark_color()
               : internal::mark_color();
}

void mark_invisble_hitbox(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const ImU32& mark_color,
    const bool   mark_is_selected
)
{
    const float mark_horizontal_size = 6.f;
    draw_mark(
        draw_list,
        mark_position,
        mark_drawing_color(mark_position, mark_horizontal_size),
        mark_color,
        mark_horizontal_size,
        mark_is_selected
    );
}

} // namespace ImGuiGradient