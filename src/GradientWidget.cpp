#include <imgui_gradient/imgui_gradient.hpp>
#include <iterator>
#include "gradient_widgets.hpp"
#include "imgui_draw.hpp"
#include "random.hpp"

namespace ImGuiGradient {

static void draw_gradient_bar(Gradient& gradient, Interpolation interpolation_mode, ImVec2 gradient_bar_pos, float width, float height)
{
    ImDrawList& draw_list           = *ImGui::GetWindowDrawList();
    const float gradient_botto_barm = gradient_bar_pos.y + height;

    draw_gradient_border(draw_list, gradient_bar_pos, ImVec2(gradient_bar_pos.x + width, gradient_botto_barm), internal::color__border());
    if (!gradient.is_empty())
    {
        draw_gradient(gradient, draw_list, interpolation_mode, gradient_bar_pos, gradient_botto_barm, width);
    }
    ImGui::SetCursorScreenPos(ImVec2(gradient_bar_pos.x, gradient_bar_pos.y + height));
}

static void handle_interactions_with_hovered_mark(Mark*& dragging_mark, Mark*& selected_mark, Mark*& mark_to_delete, Mark& hovered_mark)
{
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        dragging_mark = &hovered_mark;
        selected_mark = &hovered_mark;
    }
    if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft))
    {
        ImGui::OpenPopup("SelectedMarkColorPicker");
        selected_mark = &hovered_mark;
    }
    if (ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonMiddle))
    {
        // When we middle click to delete a non selected mark it is impossible to remove this mark in the loop
        mark_to_delete = &hovered_mark;
    }
}

static bool draw_gradient_marks(
    GradientState& state,
    Mark*&         mark_to_delete,
    const ImVec2&  gradient_bar_pos,
    float width, float height
)
{
    ImDrawList& draw_list         = *ImGui::GetWindowDrawList();
    bool        hitbox_is_hovered = false;
    for (Mark& mark_hovered : state.gradient.get_marks())
    {
        if (state.mark_to_hide != &mark_hovered)
        {
            mark_invisble_hitbox(
                draw_list,
                gradient_bar_pos + ImVec2(mark_hovered.get_position() * width, height),
                ImGui::ColorConvertFloat4ToU32(mark_hovered.color),
                state.selected_mark == &mark_hovered
            );
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
            {
                hitbox_is_hovered = true;
                handle_interactions_with_hovered_mark(state.dragging_mark, state.selected_mark, mark_to_delete, mark_hovered);
            }
        }
    }
    static constexpr float space_between_gradient_marks_and_options = 20.f;
    ImGui::SetCursorScreenPos(ImVec2(gradient_bar_pos.x, gradient_bar_pos.y + height + space_between_gradient_marks_and_options));
    return hitbox_is_hovered;
}

float position_where_to_add_next_mark(Gradient& gradient)
{
    if (gradient.is_empty())
    {
        return 0.f;
    }
    else if (gradient.get_marks().size() == 1)
    {
        return (gradient.get_marks().begin()->get_position() > 1.f - gradient.get_marks().begin()->get_position()) ? 0.f : 1.f;
    }
    else
    {
        float max_value_mark_position     = 0;
        float max_value_between_two_marks = gradient.get_marks().begin()->get_position();
        for (auto markIt = gradient.get_marks().begin(); markIt != std::prev(gradient.get_marks().end()); ++markIt)
        {
            const Mark& mark = *markIt;
            if (max_value_between_two_marks < abs(std::next(markIt)->get_position() - mark.get_position()))
            {
                max_value_mark_position     = mark.get_position();
                max_value_between_two_marks = abs(std::next(markIt)->get_position() - max_value_mark_position);
            }
        }
        if (max_value_between_two_marks < abs(1.f - std::prev(gradient.get_marks().end())->get_position()))
        {
            max_value_mark_position     = std::prev(gradient.get_marks().end())->get_position();
            max_value_between_two_marks = abs(1.f - max_value_mark_position);
        }
        return max_value_mark_position + max_value_between_two_marks / 2.f;
    }
}

auto GradientWidget::mouse_dragging(const float gradient_bar_bottom, float width, float gradient_bar_pos_x, ImGuiGradientFlags options) -> bool
{
    bool dragging = false;
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && state.dragging_mark)
    {
        state.dragging_mark = nullptr;
    }

    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && state.dragging_mark)
    {
        const float map = ImClamp((ImGui::GetIO().MousePos.x - gradient_bar_pos_x) / width, 0.f, 1.f);
        if (state.dragging_mark->get_position() != map)
        {
            state.dragging_mark->position.set(map);
            state.gradient.sort_marks();
            dragging = true;
        }
        if (!(options & ImGuiGradientFlags_NoDragDowntoDelete))
        { // hide dragging mark when mouse under gradient bar
            float diffY = ImGui::GetIO().MousePos.y - gradient_bar_bottom;
            if (diffY >= internal::gradient_mak_delete_diffy)
            {
                state.mark_to_hide = state.dragging_mark;
            }
            // do not hide it anymore when mouse on gradient bar
            if (state.mark_to_hide && diffY <= internal::gradient_mak_delete_diffy)
            {
                state.dragging_mark = state.mark_to_hide;
                state.mark_to_hide  = nullptr;
            }
        }
    }
    return dragging;
}

bool GradientWidget::gradient_editor(std::string_view label, std::default_random_engine& generator, float horizontal_margin, ImGuiGradientFlags options, ImGuiColorEditFlags flags)
{
    if (!(options & ImGuiGradientFlags_NoLabel))
    {
        ImGui::Text("%s", label.data());
        ImGui::Dummy(ImVec2{0.f, 1.5f});
    }

    const ImVec2 gradient_bar_pos    = internal::gradient_position(horizontal_margin);
    const float  width               = std::max(1.f, ImGui::GetContentRegionAvail().x - 2.f * horizontal_margin);
    const float  gradient_bar_bottom = gradient_bar_pos.y + internal::gradient_editor_height;

    ImGui::BeginGroup();
    ImGui::InvisibleButton("gradient_editor", ImVec2(width, internal::gradient_editor_height));
    draw_gradient_bar(state.gradient, interpolation_mode, gradient_bar_pos, width, internal::gradient_editor_height);

    Mark*      mark_to_delete         = nullptr;
    const bool add_mark_possible      = ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left);
    const bool mark_hitbox_is_hovered = draw_gradient_marks(state, mark_to_delete, gradient_bar_pos, width, internal::gradient_editor_height);

    bool modified = false;
    if (add_mark_possible && !mark_hitbox_is_hovered)
    {
        modified = add_mark((ImGui::GetIO().MousePos.x - gradient_bar_pos.x) / width, generator);
        ImGui::OpenPopup("SelectedMarkColorPicker");
    }

    modified |= mouse_dragging(gradient_bar_bottom, width, gradient_bar_pos.x, options);
    if (!(options & ImGuiGradientFlags_NoDragDowntoDelete))
    { // If mouse released and there is still a mark hidden, then it become a mark to delete
        if (state.mark_to_hide && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            if (state.dragging_mark && *state.dragging_mark == *state.mark_to_hide)
            {
                state.dragging_mark = nullptr;
            }
            mark_to_delete     = state.mark_to_hide;
            state.mark_to_hide = nullptr;
            modified |= true;
        }
    }
    // Remove mark_to_delete if it exists
    if (mark_to_delete)
    {
        if (state.selected_mark && *state.selected_mark == *mark_to_delete)
        {
            state.selected_mark = nullptr;
        }
        state.gradient.remove_mark(*mark_to_delete);
        modified |= true;
    }
    ImGui::EndGroup();
    const bool no_tooltip           = !(options & ImGuiGradientFlags_NoTooltip);
    const bool remove_button_exists = !(options & ImGuiGradientFlags_NoRemoveButton);
    if (!state.gradient.is_empty())
    {
        if (((remove_button_exists &&
              delete_button(internal::button_size(), no_tooltip)) ||
             ImGui::IsKeyPressed(ImGuiKey_Delete) || ImGui::IsKeyPressed(ImGuiKey_Backspace)) &&
            state.selected_mark)
        {
            state.gradient.remove_mark(*state.selected_mark);
            state.selected_mark = nullptr;
            modified |= true;
        }
    }
    const bool add_button_exists = !(options & ImGuiGradientFlags_NoAddButton);
    if (add_button_exists)
    {
        if (remove_button_exists && !state.gradient.is_empty())
        {
            ImGui::SameLine();
        }
        if (add_button(internal::button_size(), no_tooltip))
        {
            // Add a mark where there is the greater space in the gradient
            modified = add_mark(position_where_to_add_next_mark(state.gradient), generator);
        }
    }
    const bool color_edit_exists = !(options & ImGuiGradientFlags_NoColorEdit);
    if (color_edit_exists)
    {
        if ((remove_button_exists || add_button_exists) && state.selected_mark)
        {
            ImGui::SameLine();
        }
        modified |= color_button(state.selected_mark, no_tooltip, flags);
    }
    if (!(options & ImGuiGradientFlags_NoPositionSlider))
    {
        if ((remove_button_exists || add_button_exists || color_edit_exists) && state.selected_mark)
        {
            ImGui::SameLine();
        }

        if (state.selected_mark && precise_position(*state.selected_mark, width * .25f))
        {
            state.gradient.sort_marks();
            modified = true;
        }
    }

    const bool interpolation_combo_exists = !(options & ImGuiGradientFlags_NoInterpolationCombo);
    if (interpolation_combo_exists)
    {
        modified |= gradient_interpolation_mode(interpolation_mode);
    }
    const bool position_mode_combo_exists = !(options & ImGuiGradientFlags_NoPositionModeCombo);
    if (position_mode_combo_exists)
    {
        if (interpolation_combo_exists)
        {
            ImGui::SameLine();
        }
        modified |= position_mode_combo(position_mode);
    }

    if (!(options & ImGuiGradientFlags_NoRandomModeChange))
    {
        if (position_mode_combo_exists || interpolation_combo_exists)
        {
            ImGui::SameLine();
        }
        modified |= random_mode_box(random_mode, no_tooltip);
    }

    if (!(options & ImGuiGradientFlags_NoResetButton))
    {
        if (ImGui::Button("Reset"))
        {
            state = GradientState{};
            modified |= true;
        }
    }

    if (state.selected_mark)
    {
        modified |= open_color_picker_popup(*state.selected_mark, internal::button_size() * 12.f, no_tooltip, flags);
    }

    if (!(options & ImGuiGradientFlags_NoBorder))
    {
        float y_space_over_bar = 8.f;
        if (!(options & ImGuiGradientFlags_NoLabel))
        {
            y_space_over_bar = ImGui::CalcTextSize(label.data()).y * 2.3f;
        }
        float number_of_line_under_bar = 0.f;
        if (!(options & (ImGuiGradientFlags_NoRandomModeChange | ImGuiGradientFlags_NoCombo)))
        {
            number_of_line_under_bar += 1.f;
        }
        if (!(options & ImGuiGradientFlags_NoResetButton))
        {
            number_of_line_under_bar += 1.f;
        }
        if (!(options & (ImGuiGradientFlags_NoAddAndRemoveButton | ImGuiGradientFlags_NoMarkOptions)))
        {
            number_of_line_under_bar += 1.f;
        }
        const float y_space_under_bar = gradient_bar_bottom + internal::button_size() * number_of_line_under_bar;
        draw_border_widget(
            gradient_bar_pos - ImVec2(horizontal_margin + 4.f, y_space_over_bar),
            ImVec2(gradient_bar_pos.x + width + horizontal_margin + 4.f, y_space_under_bar * 1.25f),
            internal::color__border()
        );
    }

    return modified;
}

}; // namespace ImGuiGradient