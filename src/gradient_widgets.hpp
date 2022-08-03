#pragma once

#include <imgui/imgui.h>
#include <cassert>
#include "Gradient.hpp"
#include "ImGuiGradientFlags.hpp"
#include "Interpolation.hpp"
#include "PositionMode.hpp"
#include "gradient_settings.hpp"

namespace ImGuiGradient {

// TODO(ASG) Move in .cpp, and mark as static

static void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text);
        ImGui::EndTooltip();
    }
}

auto button_with_tooltip(
    const char* label,
    const char* tooltip_message,
    ImVec2      size                = ImVec2{0.f, 0.f},
    bool        should_show_tooltip = true
) -> bool
{
    const bool clicked = ImGui::Button(label, size);
    if (should_show_tooltip)
    {
        tooltip(tooltip_message);
    }
    return clicked;
}

auto position_mode_combo(PositionMode& position_mode) -> bool
{
    // Take the greater word to choose combo size
    const float size = ImGui::CalcTextSize("Mirror Repeat").x + 30.f;
    ImGui::SetNextItemWidth(size);
    return ImGui::Combo(
        "Position Mode",
        reinterpret_cast<int*>(&position_mode),
        " Clamp\0 Repeat\0 Mirror Clamp\0 Mirror Repeat\0\0"
    );
}

auto gradient_interpolation_mode(Interpolation& interpolation_mode) -> bool
{
    // Take the greater word to choose combo size
    const float size = ImGui::CalcTextSize("Constant").x + 50.f;
    ImGui::SetNextItemWidth(size);
    return ImGui::Combo(
        "Interpolation Mode",
        reinterpret_cast<int*>(&interpolation_mode),
        " Linear\0 Constant\0\0"
    );
}

auto delete_button(const float size, bool should_show_tooltip) -> bool
{
    return button_with_tooltip(
        "-",
        "Select a mark to remove it\nor middle click on it\nor drag it down",
        ImVec2{size, size},
        should_show_tooltip
    );
}

auto add_button(const float size, bool should_show_tooltip) -> bool
{
    return button_with_tooltip(
        "+",
        "Add a mark here\nor click on the gradient to choose its position",
        ImVec2{size, size},
        should_show_tooltip
    );
}

auto color_button(Mark* selected_mark, bool should_show_tooltip, ImGuiColorEditFlags flags = 0) -> bool
{
    return selected_mark &&
           ImGui::ColorEdit4(
               "##colorpicker1",
               reinterpret_cast<float*>(&selected_mark->color),
               should_show_tooltip
                   ? ImGuiColorEditFlags_NoInputs | flags
                   : ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | flags
           );
}

auto precise_position(Mark& selected_mark, const float width) -> bool
{
    ImGui::SetNextItemWidth(width);
    const float speed{1.f / width};
    return (ImGui::DragFloat(
        "##3",
        &selected_mark.get_position(),
        speed, 0.f, 1.f,
        "%.3f",
        ImGuiSliderFlags_AlwaysClamp
    ));
}

auto random_mode_box(bool& random_mode, bool should_show_tooltip) -> bool
{
    const bool modified = ImGui::Checkbox("Random Mode", &random_mode);
    if (should_show_tooltip)
    {
        tooltip("Add mark with random color");
    }
    return modified;
}

auto open_color_picker_popup(Mark& selected_mark, const float popup_size, bool should_show_tooltip, ImGuiColorEditFlags flags = 0) -> bool //
{
    if (ImGui::BeginPopup("SelectedMarkColorPicker"))
    {
        ImGui::SetNextItemWidth(popup_size);
        const bool modified = ImGui::ColorPicker4(
            "##colorpicker2",
            reinterpret_cast<float*>(&selected_mark.color),
            !should_show_tooltip
                ? flags
                : ImGuiColorEditFlags_NoTooltip | flags
        );
        ImGui::EndPopup();
        return modified;
    }
    else
    {
        return false;
    }
}

} // namespace ImGuiGradient