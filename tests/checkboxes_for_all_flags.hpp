#pragma once

#include <imgui/imgui.h>
#include "../src/Flags.hpp"

// TODO(ASG) clang-tidy says "function 'checkboxes_for_all_flags' defined in a header file; function definitions in header files can lead to ODR violations"
// TODO(ASG) use a Python script to generate that

auto checkboxes_for_all_flags() -> ImGuiGradient::Flags
{
    ImGuiGradient::Flags options = ImGuiGradient::Flag::None;

    static bool none = false;
    ImGui::Checkbox("ImGuiGradient::Flag::None", &none);
    if (none)
    {
        options |= ImGuiGradient::Flag::None;
    }
    static bool no_tool_tip = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoTooltip", &no_tool_tip);
    if (no_tool_tip)
    {
        options |= ImGuiGradient::Flag::NoTooltip;
    }
    static bool no_reset_button = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoResetButton", &no_reset_button);
    if (no_reset_button)
    {
        options |= ImGuiGradient::Flag::NoResetButton;
    }
    static bool no_label = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoLabel", &no_label);
    if (no_label)
    {
        options |= ImGuiGradient::Flag::NoLabel;
    }
    static bool no_random_mode = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoRandomModeCheckBox", &no_random_mode);
    if (no_random_mode)
    {
        options |= ImGuiGradient::Flag::NoRandomModeCheckBox;
    }
    static bool no_add_button = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoAddButton", &no_add_button);
    if (no_add_button)
    {
        options |= ImGuiGradient::Flag::NoAddButton;
    }
    static bool no_remove_button = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoRemoveButton", &no_remove_button);
    if (no_remove_button)
    {
        options |= ImGuiGradient::Flag::NoRemoveButton;
    }
    static bool no_drag_slider = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoPositionSlider", &no_drag_slider);
    if (no_drag_slider)
    {
        options |= ImGuiGradient::Flag::NoPositionSlider;
    }
    static bool no_color_edit = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoColorEdit", &no_color_edit);
    if (no_color_edit)
    {
        options |= ImGuiGradient::Flag::NoColorEdit;
    }
    static bool no_posittion_mode_combo = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoWrapModeSelector", &no_posittion_mode_combo);
    if (no_posittion_mode_combo)
    {
        options |= ImGuiGradient::Flag::NoWrapModeSelector;
    }
    static bool no_interpolation_combo = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoInterpolationSelector", &no_interpolation_combo);
    if (no_interpolation_combo)
    {
        options |= ImGuiGradient::Flag::NoInterpolationSelector;
    }
    static bool no_drag_down_to_delete = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoDragDownToDelete", &no_drag_down_to_delete);
    if (no_drag_down_to_delete)
    {
        options |= ImGuiGradient::Flag::NoDragDownToDelete;
    }
    static bool no_border = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoBorder", &no_border);
    if (no_border)
    {
        options |= ImGuiGradient::Flag::NoBorder;
    }
    static bool no_add_and_remove_button = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoAddAndRemoveButtons", &no_add_and_remove_button);
    if (no_add_and_remove_button)
    {
        options |= ImGuiGradient::Flag::NoAddAndRemoveButtons;
    }
    static bool no_mark_options = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoMarkOptions", &no_mark_options);
    if (no_mark_options)
    {
        options |= ImGuiGradient::Flag::NoMarkOptions;
    }
    static bool no_combo = false;
    ImGui::Checkbox("ImGuiGradient::Flag::NoSelector", &no_combo);
    if (no_combo)
    {
        options |= ImGuiGradient::Flag::NoSelector;
    }
    return options;
}