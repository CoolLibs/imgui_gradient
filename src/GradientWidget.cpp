#include "GradientWidget.hpp"
#include "imgui_draw.hpp"
#include "internal.hpp"
#include "widgets.hpp"

namespace ImGuiGradient {

auto GradientWidget::get_gradient() const -> const Gradient&
{
    return _state.gradient;
}

void GradientWidget::remove_mark(const Mark& mark)
{
    _state.gradient.remove_mark(mark);
}

void GradientWidget::set_mark_position(const Mark& mark, RelativePosition position)
{
    _state.gradient.set_mark_position(mark, position);
}

void GradientWidget::set_mark_color(const Mark& mark, ColorRGBA color)
{
    _state.gradient.set_mark_color(mark, color);
}

void GradientWidget::set_wrap_mode(WrapMode new_wrap_mode)
{
    _wrap_mode = new_wrap_mode;
}

void GradientWidget::set_interpolation_mode(Interpolation new_interpolation_mode)
{
    _interpolation_mode = new_interpolation_mode;
}

void GradientWidget::enable_random_color_mode(bool should_use_a_random_color_for_the_new_marks)
{
    _should_use_a_random_color_for_the_new_marks = should_use_a_random_color_for_the_new_marks;
}

void GradientWidget::reset()
{
    _state = internal::State{};
}

static void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text);
        ImGui::EndTooltip();
    }
}

static auto selector_with_tooltip(
    const char* label,
    int*        item_current_index, // TODO(ASG) Pass a reference, not a pointer!
    const char* items[],            // TODO(ASG) clang-tidy says "do not declare C-style arrays, use std::array<> instead"
    const int   number_of_items,
    const char* greater_items, // Use the longuest word to choose the selector's size
    const char* tooltips[],    // TODO(ASG) clang-tidy says "do not declare C-style arrays, use std::array<> instead"
    const bool  should_show_tooltip
) -> bool
{
    ImGuiContext& g{*GImGui};
    const auto    width{
        ImGui::CalcTextSize(greater_items).x +
        ImGui::GetFrameHeightWithSpacing() +
        g.Style.FramePadding.x * 2.f};
    ImGui::SetNextItemWidth(width);

    auto        modified{false};                                 // Here we store our selection data as an index.
    const char* combo_preview_value{items[*item_current_index]}; // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo(label, combo_preview_value))
    {
        for (int n = 0; n < number_of_items; n++)
        {
            const bool is_selected{(*item_current_index == n)};
            if (ImGui::Selectable(items[n], is_selected))
            {
                *item_current_index = n;
                modified            = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
            if (should_show_tooltip)
            {
                tooltip(tooltips[n]);
            }
        }
        ImGui::EndCombo();
    }
    return modified;
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

static auto wrap_mode_selector(WrapMode& wrap_mode, const bool should_show_tooltip) -> bool
{
    const char* items[]    = {"Clamp", "Repeat", "Mirror Repeat"}; // TODO(ASG) clang-tidy says "do not declare C-style arrays, use std::array<> instead"
    const char* tooltips[] = {                                     // TODO(ASG) clang-tidy says "do not declare C-style arrays, use std::array<> instead"
                              "Clamp mark position in range [0.,1.]",
                              "Repeat mark position in range [0.,1.]",
                              "Repeat and mirror mark position in range [0.,1.]"};

    return selector_with_tooltip(
        "Position Mode",
        reinterpret_cast<int*>(&wrap_mode),
        items,
        IM_ARRAYSIZE(items),
        "Mirror Repeat",
        tooltips,
        should_show_tooltip
    );
}

static auto gradient_interpolation_mode_selector(Interpolation& interpolation_mode, const bool should_show_tooltip) -> bool
{
    const char* items[]    = {"Linear", "Constant"}; // TODO(ASG) clang-tidy says "do not declare C-style arrays, use std::array<> instead"
    const char* tooltips[] = {                       // TODO(ASG) clang-tidy says "do not declare C-style arrays, use std::array<> instead"
                              "Linear interpolation between two marks",
                              "Constant color between two marks"};

    return selector_with_tooltip(
        "Interpolation Mode",
        reinterpret_cast<int*>(&interpolation_mode),
        items,
        IM_ARRAYSIZE(items),
        "Constant",
        tooltips,
        should_show_tooltip
    );
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
        "Add a mark here\nor click on the gradient to choose its position",
        should_show_tooltip
    );
}

static auto color_button(
    Mark*                     selected_mark,
    const bool                should_show_tooltip,
    const ImGuiColorEditFlags flags = 0
) -> bool
{
    return selected_mark &&
           ImGui::ColorEdit4(
               "##colorpicker1",
               reinterpret_cast<float*>(&selected_mark->color),
               should_show_tooltip
                   ? ImGuiColorEditFlags_NoInputs |
                         flags
                   : ImGuiColorEditFlags_NoTooltip |
                         ImGuiColorEditFlags_NoInputs |
                         flags
           );
}

static auto precise_position(
    Mark&       selected_mark,
    const float width
) -> bool
{
    const char* label{"##3"};
    return selected_mark.position.imgui_widget(label, width);
}

static auto random_mode_box(
    bool&      should_use_a_random_color_for_the_new_marks,
    const bool should_show_tooltip
) -> bool
{
    const bool modified = ImGui::Checkbox(
        "Random Mode",
        &should_use_a_random_color_for_the_new_marks
    );
    if (should_show_tooltip)
    {
        tooltip("Add mark with random color");
    }
    return modified;
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
            flags | (!should_show_tooltip ? ImGuiColorEditFlags_NoTooltip : 0)
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

static void handle_interactions_with_hovered_mark(
    const Mark*& dragged_mark,
    const Mark*& selected_mark,
    const Mark*& mark_to_delete,
    const Mark&  hovered_mark
)
{
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        dragged_mark  = &hovered_mark;
        selected_mark = &hovered_mark;
    }
    if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft))
    {
        ImGui::OpenPopup("SelectedMarkColorPicker");
        selected_mark = &hovered_mark;
    }
    if (ImGui::IsMouseReleased(ImGuiPopupFlags_MouseButtonMiddle))
    {
        mark_to_delete = &hovered_mark; // When we middle click to delete a non selected mark it is impossible to remove this mark in the loop
    }
}

auto GradientWidget::draw_gradient_marks(
    const Mark*   mark_to_delete,
    const ImVec2& gradient_bar_position,
    const ImVec2  gradient_size
) -> bool
{
    ImDrawList& draw_list         = *ImGui::GetWindowDrawList();
    bool        hitbox_is_hovered = false;
    for (const Mark& mark : _state.gradient.get_marks())
    {
        if (_state.mark_to_hide != &mark)
        {
            draw_mark(
                draw_list,
                gradient_bar_position + ImVec2{mark.position.get(), 1.f} * gradient_size,
                ImGui::ColorConvertFloat4ToU32(mark.color),
                gradient_size.y,
                _state.selected_mark == &mark
            );
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
            {
                hitbox_is_hovered = true;
                const Mark* const_dragged_mark{_state.dragged_mark};
                const Mark* const_selected_mark{_state.selected_mark};
                handle_interactions_with_hovered_mark(
                    const_dragged_mark,
                    const_selected_mark,
                    mark_to_delete,
                    mark
                );
                if (const_selected_mark)
                {
                    _state.selected_mark = const_cast<Mark*>(const_selected_mark); // TODO(ASG) Why a const_cast here ????
                }
                if (const_dragged_mark)
                {
                    _state.dragged_mark = const_cast<Mark*>(const_dragged_mark); // TODO(ASG) Why a const_cast here ????
                }
            }
        }
    }
    static constexpr float space_between_gradient_bar_and_options = 20.f;
    ImGui::SetCursorScreenPos(
        gradient_bar_position +
        ImVec2{
            0.f,
            gradient_size.y + space_between_gradient_bar_and_options}
    );
    return hitbox_is_hovered;
}

static auto position_where_to_add_next_mark(Gradient& gradient) -> float
{
    if (gradient.is_empty())
    {
        return 0.f;
    }
    else if (gradient.get_marks().size() == 1)
    {
        const auto first_position_mark = gradient.get_marks().front().position.get();
        return first_position_mark > 1.f - first_position_mark
                   ? 0.f
                   : 1.f;
    }
    else
    {
        // TODO(ASG) This deserves a comment to exmplain what you are trying to do
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
    bool is_dragging = false;
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && _state.dragged_mark)
    {
        _state.dragged_mark = nullptr;
    }
    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && _state.dragged_mark)
    {
        const auto map{ImClamp((ImGui::GetIO().MousePos.x - gradient_bar_position.x) / gradient_size.x, 0.f, 1.f)};
        if (_state.dragged_mark->position.get() != map)
        {
            _state.dragged_mark->position.set(map);
            set_mark_position(*_state.dragged_mark, _state.dragged_mark->position);
            is_dragging = true;
        }
        if (!(settings.flags & Flag::NoDragDownToDelete))
        { // hide dragging mark when mouse under gradient bar
            const auto diffY{ImGui::GetIO().MousePos.y - gradient_bar_position.y - gradient_size.y};
            if (diffY >= settings.distance_to_delete_mark_by_dragging_down)
            {
                _state.mark_to_hide = _state.dragged_mark;
            }
            // do not hide it anymore when mouse on gradient bar
            if (_state.mark_to_hide && diffY <= settings.distance_to_delete_mark_by_dragging_down)
            {
                _state.dragged_mark = _state.mark_to_hide; // TODO(ASG) I don't think this line does anything
                _state.mark_to_hide = nullptr;
            }
        }
    }
    return is_dragging;
}

static auto random(std::default_random_engine& generator) -> float
{
    return std::uniform_real_distribution<float>{0.f, 1.f}(generator);
}

static auto random_color(std::default_random_engine& generator) -> ColorRGBA
{
    return ColorRGBA{random(generator), random(generator), random(generator), 1.f};
}

void GradientWidget::add_mark(float position)
{
    const auto relative_pos = make_relative_position(position, _wrap_mode);
    _state.selected_mark =
        &_state.gradient.add_mark(
            Mark{
                RelativePosition{relative_pos},
                _state.gradient.compute_color_at(relative_pos)}
        );
}

void GradientWidget::add_mark(
    const float                 position,
    std::default_random_engine& generator
)
{
    const auto relative_pos = make_relative_position(position, _wrap_mode);
    _state.selected_mark =
        &_state.gradient.add_mark(
            Mark{RelativePosition{relative_pos}, random_color(generator)}
        );
}

static auto next_mark_after_removing_it(const std::list<Mark>& gradient, const Mark& mark) -> Mark* // TODO(ASG) I don't understand the name of this function. It is not related to removing the mark at all.
{
    if (gradient.empty() ||
        gradient.size() == 1)
    {
        return nullptr;
    }
    else if (mark == gradient.front())
    {
        return const_cast<Mark*>(&gradient.back()); // TODO(ASG) Why a const_cast here ???
    }
    else
    {
        return const_cast<Mark*>(&gradient.front()); // TODO(ASG) Why a const_cast here ???
    }
}

auto GradientWidget::widget(
    const char*                 label,
    const Settings&             settings,
    std::default_random_engine& generator
) -> bool
{
    if (!(settings.flags & Flag::NoLabel))
    {
        ImGui::Text("%s", label);
        ImGui::Dummy(ImVec2{0.f, 1.5f});
    }

    const auto gradient_bar_position = ImVec2{internal::gradient_position(settings.horizontal_margin)};
    const auto gradient_size         = ImVec2{
        std::max(1.f, ImGui::GetContentRegionAvail().x - 2.f * settings.horizontal_margin),
        settings.gradient_height};

    ImGui::BeginGroup();
    ImGui::InvisibleButton("gradient_editor", gradient_size);
    draw_gradient_bar(_state.gradient, _interpolation_mode, gradient_bar_position, gradient_size);

    Mark*      mark_to_delete{nullptr};
    const auto add_mark_possible{ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left)}; // TODO(ASG) Explain why it has to be declared a few lines before its firt use. Rename as can_add_mark
    const auto mark_hitbox_is_hovered{draw_gradient_marks(
        mark_to_delete,
        gradient_bar_position,
        gradient_size
    )};

    auto modified{false};
    if (add_mark_possible && !mark_hitbox_is_hovered)
    {
        const auto position{(ImGui::GetIO().MousePos.x - gradient_bar_position.x) / gradient_size.x};
        if (_should_use_a_random_color_for_the_new_marks)
        {
            add_mark(position, generator);
        }
        else
        {
            add_mark(position);
        }
        modified = true;
        ImGui::OpenPopup("SelectedMarkColorPicker");
    }

    modified |= mouse_dragging_interactions(gradient_bar_position, gradient_size, settings);
    if (!(settings.flags & Flag::NoDragDownToDelete))
    {
        // If mouse released and there is still a mark hidden, then it becomes a mark to delete
        if (_state.mark_to_hide && !ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            if (_state.dragged_mark &&
                *_state.dragged_mark == *_state.mark_to_hide)
            {
                _state.dragged_mark = nullptr;
            }
            mark_to_delete      = _state.mark_to_hide;
            _state.mark_to_hide = nullptr;
            modified |= true;
        }
    }
    // Remove mark_to_delete if it exists
    if (mark_to_delete)
    {
        if (_state.selected_mark &&
            *_state.selected_mark == *mark_to_delete)
        {
            _state.selected_mark = next_mark_after_removing_it(_state.gradient.get_marks(), *_state.selected_mark);
        }
        remove_mark(*mark_to_delete);
        modified |= true;
    }
    ImGui::EndGroup();
    const auto is_there_no_tooltip{!(settings.flags & Flag::NoTooltip)};
    const auto is_there_remove_button{!(settings.flags & Flag::NoRemoveButton)};
    if (!_state.gradient.is_empty())
    {
        auto window_is_hovered{ImGui::IsWindowHovered(
            ImGuiHoveredFlags_ChildWindows |
            ImGuiHoveredFlags_NoPopupHierarchy
        )};
        if (((is_there_remove_button &&
              delete_button(!_state.selected_mark, "There is no mark selected", is_there_no_tooltip)) ||
             ImGui::IsKeyPressed(ImGuiKey_Delete) ||
             ImGui::IsKeyPressed(ImGuiKey_Backspace)) &&
            _state.selected_mark &&
            window_is_hovered &&
            !ImGui::GetIO().WantTextInput)
        {
            const Mark* new_selected_mark = next_mark_after_removing_it(_state.gradient.get_marks(), *_state.selected_mark);
            remove_mark(*_state.selected_mark);
            _state.selected_mark = const_cast<Mark*>(new_selected_mark); // TODO(ASG) Why a const_cast here ???
            modified |= true;
        }
    }
    const auto is_there_add_button{!(settings.flags & Flag::NoAddButton)};
    if (is_there_add_button)
    {
        if (is_there_remove_button &&
            !_state.gradient.is_empty())
        {
            ImGui::SameLine();
        }
        if (add_button(is_there_no_tooltip))
        {
            // Add a mark where there is the greater space in the gradient
            const auto position{position_where_to_add_next_mark(_state.gradient)};
            if (_should_use_a_random_color_for_the_new_marks) // TODO(ASG) I have already seen that bit of logic
            {                                                 // it
                add_mark(position, generator);                // is
            }                                                 // duplicated!
            else                                              // !
            {                                                 // !
                add_mark(position);                           // !
            }                                                 // !
            modified = true;
        }
    }
    const auto is_there_color_edit{!(settings.flags & Flag::NoColorEdit)};
    if (is_there_color_edit)
    {
        if ((is_there_remove_button || is_there_add_button) &&
            _state.selected_mark)
        {
            ImGui::SameLine();
        }
        modified |= color_button(_state.selected_mark, is_there_no_tooltip, settings.color_flags);
    }
    if (!(settings.flags & Flag::NoPositionSlider))
    {
        if ((is_there_remove_button || is_there_add_button || is_there_color_edit) &&
            _state.selected_mark)
        {
            ImGui::SameLine();
        }

        if (_state.selected_mark &&
            precise_position(*_state.selected_mark, gradient_size.x * .25f)) // TODO(ASG) rename precise_position to make it clear that this creates an imgui widget, e.g. position_widget
        {
            set_mark_position(*_state.selected_mark, _state.selected_mark->position);
            modified = true;
        }
    }

    const auto is_there_interpolation_selector{!(settings.flags & Flag::NoInterpolationSelector)};
    if (is_there_interpolation_selector)
    {
        modified |= gradient_interpolation_mode_selector(_interpolation_mode, is_there_no_tooltip);
    }
    const auto is_there_position_mode_selector{!(settings.flags & Flag::NoWrapModeSelector)};
    if (is_there_position_mode_selector)
    {
        if (is_there_interpolation_selector)
        {
            ImGui::SameLine();
        }
        modified |= wrap_mode_selector(_wrap_mode, is_there_no_tooltip);
    }

    if (!(settings.flags & Flag::NoRandomModeCheckBox))
    {
        if (is_there_position_mode_selector || is_there_interpolation_selector)
        {
            ImGui::SameLine();
        }
        modified |= random_mode_box(_should_use_a_random_color_for_the_new_marks, is_there_no_tooltip);
    }

    if (!(settings.flags & Flag::NoResetButton))
    {
        if (ImGui::Button("Reset"))
        {
            reset();
            modified |= true;
        }
    }

    if (_state.selected_mark)
    {
        static const auto picker_popup_size{internal::line_height() * 12.f};
        modified |= open_color_picker_popup(
            *_state.selected_mark,
            picker_popup_size,
            is_there_no_tooltip,
            settings.flags
        );
    }

    if (!(settings.flags & Flag::NoBorder))
    {
        ImGuiContext& g{*GImGui};

        auto space_over_bar{g.Style.ItemSpacing.y * 4.f};
        if (!(settings.flags & Flag::NoLabel))
        {
            space_over_bar += ImGui::CalcTextSize(label).y;
        }
        auto number_of_line_under_bar{1.f};
        if (!(settings.flags & Flag::NoRandomModeCheckBox) ||
            !(settings.flags & Flag::NoSelector))
        {
            number_of_line_under_bar += 1.f;
        }
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
        ImDrawList& draw_list{*ImGui::GetWindowDrawList()};

        const auto space_under_bar{
            (internal::line_height() + g.Style.ItemSpacing.y) * number_of_line_under_bar +
            g.Style.ItemSpacing.y * 2.f};
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

    return modified;
}

auto GradientWidget::widget(const char* label, const Settings& settings) -> bool
{
    static std::default_random_engine generator{std::random_device{}()};
    return widget(label, settings, generator);
}

}; // namespace ImGuiGradient
