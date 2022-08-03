#pragma once

#include <imgui/imgui.h>
#include "../src/ImGuiGradientFlags.hpp"

auto gradient_options_debug() -> ImGuiGradientFlags
{
    ImGuiGradientFlags options = ImGuiGradient::Flags::None;

    static bool none = false;
    ImGui::Checkbox("ImGuiGradient::Flags::None", &none);
    if (none)
    {
        options |= ImGuiGradient::Flags::None;
    }
    static bool no_tool_tip = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoTooltip", &no_tool_tip);
    if (no_tool_tip)
    {
        options |= ImGuiGradient::Flags::NoTooltip;
    }
    static bool no_reset_button = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoResetButton", &no_reset_button);
    if (no_reset_button)
    {
        options |= ImGuiGradient::Flags::NoResetButton;
    }
    static bool no_label = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoLabel", &no_label);
    if (no_label)
    {
        options |= ImGuiGradient::Flags::NoLabel;
    }
    static bool no_random_mode = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoRandomModeChange", &no_random_mode);
    if (no_random_mode)
    {
        options |= ImGuiGradient::Flags::NoRandomModeChange;
    }
    static bool no_add_button = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoAddButton", &no_add_button);
    if (no_add_button)
    {
        options |= ImGuiGradient::Flags::NoAddButton;
    }
    static bool no_remove_button = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoRemoveButton", &no_remove_button);
    if (no_remove_button)
    {
        options |= ImGuiGradient::Flags::NoRemoveButton;
    }
    static bool no_drag_slider = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoPositionSlider", &no_drag_slider);
    if (no_drag_slider)
    {
        options |= ImGuiGradient::Flags::NoPositionSlider;
    }
    static bool no_color_edit = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoColorEdit", &no_color_edit);
    if (no_color_edit)
    {
        options |= ImGuiGradient::Flags::NoColorEdit;
    }
    static bool no_posittion_mode_combo = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoWrapModeCombo", &no_posittion_mode_combo);
    if (no_posittion_mode_combo)
    {
        options |= ImGuiGradient::Flags::NoWrapModeCombo;
    }
    static bool no_interpolation_combo = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoInterpolationCombo", &no_interpolation_combo);
    if (no_interpolation_combo)
    {
        options |= ImGuiGradient::Flags::NoInterpolationCombo;
    }
    static bool no_drag_down_to_delete = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoDragDowntoDelete", &no_drag_down_to_delete);
    if (no_drag_down_to_delete)
    {
        options |= ImGuiGradient::Flags::NoDragDowntoDelete;
    }
    static bool no_border = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoBorder", &no_border);
    if (no_border)
    {
        options |= ImGuiGradient::Flags::NoBorder;
    }
    static bool no_add_and_remove_button = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoAddAndRemoveButton", &no_add_and_remove_button);
    if (no_add_and_remove_button)
    {
        options |= ImGuiGradient::Flags::NoAddAndRemoveButton;
    }
    static bool no_mark_options = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoMarkOptions", &no_mark_options);
    if (no_mark_options)
    {
        options |= ImGuiGradient::Flags::NoMarkOptions;
    }
    static bool no_combo = false;
    ImGui::Checkbox("ImGuiGradient::Flags::NoCombo", &no_combo);
    if (no_combo)
    {
        options |= ImGuiGradient::Flags::NoCombo;
    }
    return options;
}