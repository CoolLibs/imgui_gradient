#include "Gradient.hpp"
#include "Interpolation.hpp"
#include "Settings.hpp"
#include "internal.hpp"

// TODO(ASG) Make the delete button disabled if there is no selected mark

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
    ImDrawList&         draw_list,
    Gradient&           gradient,
    const Interpolation interpolation_mode,
    const ImVec2        gradient_position,
    const ImVec2        size
)
{
    float current_starting_x = gradient_position.x;
    for (auto mark_iterator = gradient.get_marks().begin(); mark_iterator != gradient.get_marks().end(); ++mark_iterator)
    {
        const Mark& mark = *mark_iterator;

        const auto color_right = ImU32{ImGui::ColorConvertFloat4ToU32(mark.color)};

        const auto from{current_starting_x};
        const auto to{gradient_position.x + mark.position.get() * (size.x)};
        if (mark.position.get() != 0.f)
        {
            if (interpolation_mode == Interpolation::Linear)
            {
                const ImU32 color_left = (mark_iterator != gradient.get_marks().begin())
                                             ? ImGui::ColorConvertFloat4ToU32(std::prev(mark_iterator)->color)
                                             : color_right;
                draw_gradient_between_two_colors(
                    draw_list,
                    ImVec2(from, gradient_position.y),
                    ImVec2(to, gradient_position.y + size.y),
                    color_left, color_right
                );
            }
            else
            {
                draw_uniform_square(
                    draw_list,
                    ImVec2(from, gradient_position.y),
                    ImVec2(to, gradient_position.y + size.y),
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
            ImVec2(current_starting_x, gradient_position.y),
            ImVec2(gradient_position.x + size.x, gradient_position.y + size.y),
            ImGui::ColorConvertFloat4ToU32(gradient.get_marks().back().color)
        );
    }
}

static auto mark_invisible_button(
    const ImVec2 position_to_draw_mark,
    const float  mark_square_size,
    const float  gradient_height
) -> bool
{
    ImGui::SetCursorScreenPos(position_to_draw_mark - ImVec2{mark_square_size * 1.5f, gradient_height});
    const auto button_size = ImVec2{
        mark_square_size * 3.f,
        gradient_height + mark_square_size * 2.f};
    ImGui::InvisibleButton("mark", button_size);
    return ImGui::IsItemHovered();
}

static auto mark_drawing_color(
    const ImVec2 position_to_draw_mark,
    const float  mark_square_size,
    const float  gradient_height
) -> ImU32
{
    return mark_invisible_button(position_to_draw_mark, mark_square_size, gradient_height)
               ? internal::hovered_mark_color()
               : internal::mark_color();
}

static void draw_background_mark(
    ImDrawList&  draw_list,
    const ImVec2 position_to_draw_mark,
    const float  mark_square_size,
    const float  gradient_height
)
{
    const auto mark_color = mark_drawing_color(position_to_draw_mark, mark_square_size, gradient_height);

    const auto mark_top_triangle    = ImVec2{0.f, -mark_square_size};
    const auto mark_bottom_triangle = ImVec2{mark_square_size, 0.f};
    draw_list.AddTriangleFilled(
        position_to_draw_mark + mark_top_triangle,
        position_to_draw_mark - mark_bottom_triangle,
        position_to_draw_mark + mark_bottom_triangle,
        mark_color
    );

    const auto mark_top_left_corner =
        ImVec2{-mark_square_size, 0.f};
    const auto mark_bottom_right_corner =
        ImVec2{
            mark_square_size,
            2.f * mark_square_size};
    draw_uniform_square(
        draw_list,
        position_to_draw_mark + mark_top_left_corner,
        position_to_draw_mark + mark_bottom_right_corner,
        mark_color
    );

    static constexpr auto offset_between_mark_square_and_mark_square_inside = ImVec2{1.f, 1.f};
    draw_uniform_square(
        draw_list,
        position_to_draw_mark + mark_top_left_corner + offset_between_mark_square_and_mark_square_inside,
        position_to_draw_mark + mark_bottom_right_corner - offset_between_mark_square_and_mark_square_inside,
        mark_color
    );
}

static void draw_mark_selected(
    ImDrawList&  draw_list,
    const ImVec2 position_to_draw_mark,
    const float  mark_square_size
)
{
    const auto            selected_mark_color = internal::selected_mark_color();
    static constexpr auto offset_between_mark_and_selected_mark{1.f};

    static constexpr auto mark_selected_triangle_size{4.f};
    static constexpr auto mark_top_triangle =
        ImVec2{
            0.f,
            -mark_selected_triangle_size - offset_between_mark_and_selected_mark};
    static constexpr auto mark_bottom_right_triangle =
        ImVec2{
            -mark_selected_triangle_size,
            offset_between_mark_and_selected_mark};
    static constexpr auto mark_bottom_left_triangle =
        ImVec2{
            mark_selected_triangle_size,
            offset_between_mark_and_selected_mark};

    draw_list.AddTriangleFilled(
        position_to_draw_mark + mark_top_triangle,
        position_to_draw_mark + mark_bottom_right_triangle,
        position_to_draw_mark + mark_bottom_left_triangle,
        selected_mark_color
    );

    const auto mark_selected_square_size{mark_square_size - offset_between_mark_and_selected_mark};
    const auto mark_top_left_corner =
        ImVec2{
            -mark_selected_square_size,
            offset_between_mark_and_selected_mark};
    const auto mark_bottom_right_corner =
        ImVec2{
            mark_selected_square_size,
            2.f * mark_selected_square_size + offset_between_mark_and_selected_mark};

    static constexpr auto rounding = 1.f;
    draw_list.AddRect(
        position_to_draw_mark + mark_top_left_corner,
        position_to_draw_mark + mark_bottom_right_corner,
        selected_mark_color,
        rounding,
        ImDrawFlags_Closed
    );
}

void draw_mark(
    ImDrawList&  draw_list,
    const ImVec2 position_to_draw_mark,
    const ImU32& mark_color,
    const float  gradient_height,
    const bool   mark_is_selected
)
{
    static constexpr auto mark_square_size{6.f};
    draw_background_mark(
        draw_list,
        position_to_draw_mark,
        mark_square_size,
        gradient_height
    );
    if (mark_is_selected)
    {
        draw_mark_selected(
            draw_list,
            position_to_draw_mark,
            mark_square_size
        );
    }

    static constexpr auto square_size{3.f};
    static constexpr auto mark_top_left_corner =
        ImVec2{-square_size, square_size};
    static constexpr auto mark_bottom_right_corner =
        ImVec2{square_size, square_size * square_size};
    draw_uniform_square(
        draw_list,
        position_to_draw_mark + mark_top_left_corner,
        position_to_draw_mark + mark_bottom_right_corner,
        mark_color
    );
}

} // namespace ImGuiGradient