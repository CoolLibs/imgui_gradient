#include "GradientWidget.hpp"
#include <array>
#include "button_disabled.hpp"
#include "imgui_draw.hpp"
#include "internal.hpp"
#include "tooltip.hpp"

namespace ImGG {

static auto random(std::default_random_engine& generator) -> float
{
    return std::uniform_real_distribution<float>{0.f, 1.f}(generator);
}

static auto random_color(std::default_random_engine& generator) -> ColorRGBA
{
    return ColorRGBA{random(generator), random(generator), random(generator), 1.f};
}

void GradientWidget::add_mark_with_chosen_mode(const RelativePosition relative_pos, std::default_random_engine& generator, bool add_a_random_color)
{
    const auto mark = Mark{
        relative_pos,
        add_a_random_color
            ? random_color(generator)
            : _gradient.at(relative_pos)};
    _selected_mark = _gradient.add_mark(mark);
}

static auto button_with_tooltip(
    const char* label,
    const char* tooltip_message,
    const bool  should_show_tooltip = true
) -> bool
{
    const bool clicked = ImGui::Button(label, internal::button_size());
    if (should_show_tooltip)
    {
        tooltip(tooltip_message);
    }
    return clicked;
}

static auto delete_button(const bool disable, const char* reason_for_disabling, const bool should_show_tooltip) -> bool
{
    if (disable)
    {
        button_disabled("-", reason_for_disabling, internal::button_size());
        return false;
    }
    else
    {
        return button_with_tooltip(
            "-",
            "Removes the selected mark.\nYou can also middle click on it,\nor drag it down.",
            should_show_tooltip
        );
    }
}

static auto add_button(const bool should_show_tooltip) -> bool
{
    return button_with_tooltip(
        "+",
        "Add a mark here\nor click on the gradient to choose its position.",
        should_show_tooltip
    );
}

static auto color_button(
    Mark&                     selected_mark,
    const bool                should_show_tooltip,
    const ImGuiColorEditFlags flags = 0
) -> bool
{
    return ImGui::ColorEdit4(
        "##colorpicker1",
        reinterpret_cast<float*>(&selected_mark.color),
        flags | ImGuiColorEditFlags_NoInputs | (should_show_tooltip ? 0 : ImGuiColorEditFlags_NoTooltip)
    );
}

static auto open_color_picker_popup(
    Mark&                     selected_mark,
    const float               popup_size,
    const bool                should_show_tooltip,
    const ImGuiColorEditFlags flags = 0
) -> bool
{
    if (ImGui::BeginPopup("SelectedMarkColorPicker"))
    {
        ImGui::SetNextItemWidth(popup_size);
        const bool modified = ImGui::ColorPicker4(
            "##colorpicker2",
            reinterpret_cast<float*>(&selected_mark.color),
            flags | (should_show_tooltip ? 0 : ImGuiColorEditFlags_NoTooltip)
        );
        ImGui::EndPopup();
        return modified;
    }
    else
    {
        return false;
    }
}

static void draw_gradient_bar(
    Gradient&           gradient,
    const Interpolation interpolation_mode,
    const ImVec2        gradient_bar_position,
    const ImVec2        gradient_size
)
{
    ImDrawList& draw_list = *ImGui::GetWindowDrawList();
    draw_border(
        draw_list,
        gradient_bar_position,
        gradient_bar_position + gradient_size
    );
    if (!gradient.is_empty())
    {
        draw_gradient(
            draw_list,
            gradient,
            interpolation_mode,
            gradient_bar_position,
            gradient_size
        );
    }
    ImGui::SetCursorScreenPos(
        gradient_bar_position +
        ImVec2{0.f, gradient_size.y}
    );
}

// TODO(ASG) Fix border
// TODO(ASG) Fix SameLine() after a gradient

static void handle_interactions_with_hovered_mark(
    MarkId& dragged_mark,
    MarkId& selected_mark,
    MarkId& mark_to_delete,
    MarkId  hovered_mark
)
{
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        dragged_mark  = hovered_mark;
        selected_mark = hovered_mark;
    }
    if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft))
    {
        ImGui::OpenPopup("SelectedMarkColorPicker");
        selected_mark = hovered_mark;
    }
    if (ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonMiddle))
    {
        mark_to_delete = hovered_mark; // When we middle click to delete a non selected mark it is impossible to remove this mark in the loop
    }
}

auto GradientWidget::draw_gradient_marks(
    MarkId&      mark_to_delete,
    const ImVec2 gradient_bar_position,
    const ImVec2 gradient_size
) -> bool
{
    ImDrawList& draw_list         = *ImGui::GetWindowDrawList();
    bool        hitbox_is_hovered = false;
    for (const Mark& mark : _gradient.get_marks())
    {
        MarkId current_mark_id{mark};
        if (_mark_to_hide != current_mark_id)
        {
            draw_mark(
                draw_list,
                gradient_bar_position + ImVec2{mark.position.get(), 1.f} * gradient_size,
                ImGui::ColorConvertFloat4ToU32(mark.color),
                gradient_size.y,
                _selected_mark == current_mark_id
            );
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
            {
                hitbox_is_hovered = true;
                handle_interactions_with_hovered_mark(
                    _dragged_mark,
                    _selected_mark,
                    mark_to_delete,
                    current_mark_id
                );
            }
        }
    }
    ImGui::SetCursorScreenPos(
        gradient_bar_position +
        ImVec2{
            0.f,
            gradient_size.y + ImGui::GetStyle().ItemSpacing.y * 2.f}
    );
    return hitbox_is_hovered;
}

static auto position_where_to_add_next_mark(const Gradient& gradient) -> float
{
    if (gradient.is_empty())
    {
        return 0.f;
    }
    else if (gradient.get_marks().size() == 1)
    {
        const auto first_position_mark = gradient.get_marks().front().position.get();
        return first_position_mark > 0.5f
                   ? 0.f
                   : 1.f;
    }
    else
    {
        // Find where is the bigger space between two marks
        // to return the position between these two marks.
        const auto first_mark_iterator{gradient.get_marks().begin()};
        const auto last_mark_iterator{std::prev(gradient.get_marks().end())};
        auto       max_value_mark_position{0.f};
        auto       max_value_between_two_marks{first_mark_iterator->position.get()};
        for (auto mark_iterator = first_mark_iterator; mark_iterator != last_mark_iterator; ++mark_iterator)
        {
            const Mark& mark{*mark_iterator};
            const auto  mark_next_iterator{std::next(mark_iterator)->position.get()};
            const auto  mark_position{mark.position.get()};
            if (max_value_between_two_marks < abs(mark_next_iterator - mark_position))
            {
                max_value_mark_position     = mark_position;
                max_value_between_two_marks = abs(mark_next_iterator - max_value_mark_position);
            }
        }
        const auto last_mark_position{last_mark_iterator->position.get()};
        if (max_value_between_two_marks < abs(1.f - last_mark_position))
        {
            max_value_mark_position     = last_mark_position;
            max_value_between_two_marks = abs(1.f - max_value_mark_position);
        }
        return max_value_mark_position + max_value_between_two_marks / 2.f;
    }
}

auto GradientWidget::mouse_dragging_interactions(
    const ImVec2    gradient_bar_position,
    const ImVec2    gradient_size,
    const Settings& settings
) -> bool
{
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        _dragged_mark.reset();
    }
    bool        is_dragging  = false;
    auto* const drag_mark_id = gradient().find(_dragged_mark);
    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && drag_mark_id)
    {
        const auto map{ImClamp((ImGui::GetIO().MousePos.x - gradient_bar_position.x) / gradient_size.x, 0.f, 1.f)};
        if (drag_mark_id->position.get() != map)
        {
            gradient().set_mark_position(_dragged_mark, RelativePosition{map});
            is_dragging = true;
        }
        if (!(settings.flags & Flag::NoDragDownToDelete))
        { // hide dragging mark when mouse under gradient bar
            const auto diffY{ImGui::GetIO().MousePos.y - gradient_bar_position.y - gradient_size.y};
            if (diffY >= settings.distance_to_delete_mark_by_dragging_down)
            {
                _mark_to_hide = _dragged_mark;
            }
            // do not hide it anymore when mouse on gradient bar
            if (_gradient.contains(_mark_to_hide) && diffY <= settings.distance_to_delete_mark_by_dragging_down)
            {
                _mark_to_hide.reset();
            }
        }
    }
    return is_dragging;
}

static auto next_selected_mark(const std::list<Mark>& gradient, MarkId mark) -> MarkId
{
    assert(!gradient.empty());
    if (gradient.size() == 1)
    {
        return MarkId{};
    }
    else if (mark == MarkId{gradient.front()})
    {
        return MarkId{gradient.back()};
    }
    else
    {
        return MarkId{gradient.front()};
    };
}

auto GradientWidget::widget(
    const char*                 label,
    std::default_random_engine& generator,
    const Settings&             settings
) -> bool
{
    ImGui::PushID(label);
    ImGui::BeginGroup();
    if (!(settings.flags & Flag::NoLabel))
    {
        ImGui::Text("%s", label);
        ImGui::Dummy(ImVec2{0.f, 1.5f});
    }

    const auto gradient_bar_position = ImVec2{internal::gradient_position(settings.horizontal_margin)};
    const auto gradient_size         = ImVec2{
        std::max(1.f, ImGui::GetContentRegionAvail().x - 2.f * settings.horizontal_margin),
        settings.gradient_height,
    };

    ImGui::BeginGroup();
    ImGui::InvisibleButton("gradient_editor", gradient_size);
    draw_gradient_bar(_gradient, settings.interpolation_mode, gradient_bar_position, gradient_size);

    const auto wants_to_add_mark{ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)}; // We need to declare it before drawing the marks because we want to
                                                                                                          // test if the mouse is hovering the gradient bar not the marks.
    MarkId     mark_to_delete{};
    const auto mark_hitbox_is_hovered = draw_gradient_marks( // We declare it here because even if we cannot add a mark we need to draw gradient marks.
        mark_to_delete,
        gradient_bar_position,
        gradient_size
    );

    auto modified{false};
    if (wants_to_add_mark && !mark_hitbox_is_hovered)
    {
        const auto position{(ImGui::GetIO().MousePos.x - gradient_bar_position.x) / gradient_size.x};
        add_mark_with_chosen_mode({position, WrapMode::Clamp}, generator, settings.should_use_a_random_color_for_the_new_marks);
        modified = true;
        ImGui::OpenPopup("SelectedMarkColorPicker");
    }

    modified |= mouse_dragging_interactions(gradient_bar_position, gradient_size, settings);
    if (!(settings.flags & Flag::NoDragDownToDelete))
    {
        // If mouse released and there is still a mark hidden, then it becomes a mark to delete
        if (_gradient.contains(_mark_to_hide) && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            mark_to_delete = _mark_to_hide;
        }
    }
    // Remove mark_to_delete if it exists
    if (_gradient.contains(mark_to_delete))
    {
        if (_gradient.contains(_selected_mark) &&
            _selected_mark == mark_to_delete)
        {
            _selected_mark = next_selected_mark(_gradient.get_marks(), _selected_mark);
        }
        gradient().remove_mark(mark_to_delete);
        modified = true;
    }
    ImGui::EndGroup();
    const auto is_there_a_tooltip{!(settings.flags & Flag::NoTooltip)};
    const auto is_there_remove_button{!(settings.flags & Flag::NoRemoveButton)};
    if (!_gradient.is_empty())
    {
        const auto window_is_hovered{ImGui::IsWindowHovered(
            ImGuiHoveredFlags_ChildWindows |
            ImGuiHoveredFlags_AllowWhenBlockedByActiveItem
        )};

        // TODO(ASG) Test that this still works
        const auto delete_button_pressed = is_there_remove_button
                                               ? delete_button(!_gradient.contains(_selected_mark), "There is no mark selected", is_there_a_tooltip)
                                               : false;

        const auto delete_key_pressed = window_is_hovered &&
                                        !ImGui::GetIO().WantTextInput &&
                                        (ImGui::IsKeyPressed(ImGuiKey_Delete) || ImGui::IsKeyPressed(ImGuiKey_Backspace));

        const auto wants_to_delete = delete_button_pressed || delete_key_pressed;
        if (wants_to_delete && _gradient.contains(_selected_mark))
        {
            const MarkId new_selected_mark = next_selected_mark(_gradient.get_marks(), _selected_mark);
            gradient().remove_mark(_selected_mark);
            _selected_mark = new_selected_mark;
            modified       = true;
        }
    }

    const auto is_there_add_button{!(settings.flags & Flag::NoAddButton)};
    if (is_there_add_button)
    {
        if (is_there_remove_button &&
            !_gradient.is_empty())
        {
            ImGui::SameLine();
        }
        if (add_button(is_there_a_tooltip))
        {
            const auto position = RelativePosition{position_where_to_add_next_mark(_gradient), WrapMode::Clamp};
            add_mark_with_chosen_mode(position, generator, settings.should_use_a_random_color_for_the_new_marks);
            modified = true;
        }
    }

    const auto selected_mark = gradient().find(_selected_mark);
    if (selected_mark)
    {
        const auto is_there_color_edit{!(settings.flags & Flag::NoColorEdit)};
        if (is_there_color_edit)
        {
            if (is_there_remove_button || is_there_add_button)
            {
                ImGui::SameLine();
            }
            modified |= color_button(*selected_mark, is_there_a_tooltip, settings.color_edit_flags);
        }

        if (!(settings.flags & Flag::NoPositionSlider))
        {
            if ((is_there_remove_button || is_there_add_button || is_there_color_edit))
            {
                ImGui::SameLine();
            }
            auto position = selected_mark->position; // Make a copy, we can't modify the position directly because we need to pass through set_mark_position() because it has some invariants to presere (sorting the marks)
            if (position.imgui_widget("##3", gradient_size.x * 0.25f))
            {
                gradient().set_mark_position(_selected_mark, position);
                modified = true;
            }
        }
    }

    if (!(settings.flags & Flag::NoResetButton))
    {
        if (ImGui::Button("Reset"))
        {
            _gradient = {};
            modified  = true;
        }
    }

    if (selected_mark) // Optimization, we don't need to even check if the popup was opened if there is no selected mark
    {
        const auto picker_popup_size{internal::line_height() * 12.f};
        modified |= open_color_picker_popup(
            *selected_mark,
            picker_popup_size,
            is_there_a_tooltip,
            settings.flags
        );
    }

    const auto space_over_bar = !(settings.flags & Flag::NoLabel)
                                    ? ImGui::CalcTextSize(label).y + ImGui::GetStyle().ItemSpacing.y * 4.f
                                    : ImGui::GetStyle().ItemSpacing.y * 2.f;
    // ImGui::SetCursorScreenPos(
    //     internal::gradient_position(0.f) + ImVec2{0.f, space_over_bar}
    // );
    auto space_under_bar{0.f};
    if (!(settings.flags & Flag::NoBorder))
    {
        auto number_of_line_under_bar{0.f};
        if (!(settings.flags & Flag::NoResetButton))
        {
            number_of_line_under_bar += 1.f;
        }
        if (!(settings.flags & Flag::NoAddButton) ||
            !(settings.flags & Flag::NoRemoveButton) ||
            !(settings.flags & Flag::NoPositionSlider) ||
            !(settings.flags & Flag::NoColorEdit))
        {
            number_of_line_under_bar += 1.f;
        }
        space_under_bar =
            (internal::line_height() + ImGui::GetStyle().ItemSpacing.y * 2.f) * number_of_line_under_bar + ImGui::GetStyle().ItemSpacing.y * 4.f;
        ImDrawList& draw_list{*ImGui::GetWindowDrawList()};
        draw_border(
            draw_list,
            gradient_bar_position -
                ImVec2{settings.horizontal_margin + 4.f, space_over_bar},
            gradient_bar_position +
                gradient_size +
                ImVec2{
                    settings.horizontal_margin + 4.f,
                    space_under_bar}
        );
    }
    ImGui::SetCursorScreenPos(ImVec2{0.f, space_under_bar + space_over_bar + ImGui::GetStyle().ItemSpacing.y * 22.f}
    );
    ImGui::EndGroup();
    ImGui::PopID();
    return modified;
}
// TODO(ASG) Make a nice rendering of the arks, make sure the triangle doesn't go outside of the square
auto GradientWidget::widget(const char* label, const Settings& settings) -> bool
{
    static std::default_random_engine generator{std::random_device{}()};
    return widget(label, generator, settings);
}
}; // namespace ImGG
