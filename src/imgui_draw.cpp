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
    static constexpr auto rounding{1.f};
    draw_list.AddRectFilled(
        top_left_corner,
        bottom_rigth_corner,
        color,
        rounding,
        ImDrawFlags_Closed
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

        const auto color_right = ImU32{ImGui::ColorConvertFloat4ToU32(mark.color)};

        const auto from{current_starting_x};
        const auto to{gradient_pos.x + mark.position.get() * (size.x)};
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

static auto mark_invisible_button(
    const ImVec2 mark_position,
    const float  mark_square_size
) -> bool
{
    ImGui::SetCursorScreenPos(mark_position - ImVec2{mark_square_size * 1.5f, 0.f});
    const auto button_size = ImVec2{
        mark_square_size * 3.f,
        mark_square_size * 2.f};
    ImGui::InvisibleButton("mark", button_size);
    return ImGui::IsItemHovered();
}

static auto mark_drawing_color(
    const ImVec2 mark_position,
    const float  mark_square_size
) -> ImU32
{
    return mark_invisible_button(mark_position, mark_square_size)
               ? internal::hovered_mark_color()
               : internal::mark_color();
}

static void draw_background_mark(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const float  mark_square_size,
    const float  offset
)
{
    const auto mark_color = mark_drawing_color(mark_position, mark_square_size);

    const auto mark_inside_border{mark_square_size - offset};

    const auto mark_square_size_x = ImVec2{mark_square_size, 0.f};
    const auto mark_square_size_y = ImVec2{0.f, mark_square_size};

    const auto offset_y = ImVec2{0.f, offset};

    const auto mark_inside_border_x = ImVec2{mark_inside_border, 0.f};
    const auto mark_inside_border_y = ImVec2{0.f, mark_inside_border};

    draw_list.AddTriangleFilled(
        mark_position - mark_square_size_y,
        mark_position - mark_square_size_x,
        mark_position + mark_square_size_x,
        mark_color
    );
    draw_uniform_square(
        draw_list,
        mark_position - mark_square_size_x,
        mark_position + mark_square_size_x + ImVec2{0.f, 2.f} * mark_square_size_y,
        mark_color
    );
    draw_uniform_square(
        draw_list,
        mark_position - mark_inside_border_x + offset_y,
        mark_position + mark_inside_border_x + ImVec2{0.f, 2.f} * mark_inside_border_y + offset_y,
        mark_color
    );
}

static void draw_arrow_selected(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const float  mark_inside_border,
    const float  mark_selected_square_size,
    const float  offset
)
{
    const auto offset_y = ImVec2{0.f, offset};

    const auto mark_inside_border_x = ImVec2{mark_inside_border, 0.f};
    const auto mark_inside_border_y = ImVec2{0.f, mark_inside_border};

    const auto mark_selected_square_size_x = ImVec2{mark_selected_square_size, 0.f};
    const auto mark_selected_square_size_y = ImVec2{0.f, mark_selected_square_size};

    const auto selected_mark_color = internal::selected_mark_color();

    draw_list.AddTriangleFilled(
        mark_position - mark_selected_square_size_y - offset_y,
        mark_position + offset_y - mark_selected_square_size_x, mark_position + mark_selected_square_size_x + offset_y,
        selected_mark_color
    );

    static constexpr auto rounding = 1.f;
    draw_list.AddRect(
        mark_position - mark_inside_border_x + offset_y,
        mark_position + mark_inside_border_x + ImVec2{0.f, 2.f} * mark_inside_border_y + offset_y,
        selected_mark_color,
        rounding,
        ImDrawFlags_Closed
    );
}

void draw_mark(
    ImDrawList&  draw_list,
    const ImVec2 mark_position,
    const ImU32& mark_color,
    bool         mark_is_selected
)
{
    static constexpr auto mark_square_size{6.f};
    static constexpr auto offset{1.f};

    draw_background_mark(
        draw_list,
        mark_position,
        mark_square_size,
        offset
    );
    if (mark_is_selected)
    {
        static constexpr auto mark_selected_square_size{4.f};
        static constexpr auto mark_inside_border{mark_square_size - offset};

        draw_arrow_selected(
            draw_list,
            mark_position,
            mark_inside_border, mark_selected_square_size, offset
        );
    }

    static constexpr auto square_height{3.f};
    static constexpr auto square_height_x = ImVec2{square_height, 0.f};
    static constexpr auto square_height_y = ImVec2{0.f, square_height};
    draw_uniform_square(
        draw_list,
        mark_position - square_height_x + square_height_y,
        mark_position + square_height_x + square_height_y * square_height_y,
        mark_color
    );
}

} // namespace ImGuiGradient