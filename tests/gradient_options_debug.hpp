#pragma once

#include <imgui/imgui.h>
#include "../src/ImGuiGradientFlags.hpp"

auto gradient_options_debug() -> ImGuiGradientFlags
{
    ImGuiGradientFlags options = ImGuiGradientFlags_None;

    static bool none = false;
    ImGui::Checkbox("ImGuiGradientFlags_None", &none);
    if (none)
    {
        options |= ImGuiGradientFlags_None;
    }
    static bool no_tool_tip = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoTooltip", &no_tool_tip);
    if (no_tool_tip)
    {
        options |= ImGuiGradientFlags_NoTooltip;
    }
    static bool no_reset_button = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoResetButton", &no_reset_button);
    if (no_reset_button)
    {
        options |= ImGuiGradientFlags_NoResetButton;
    }
    static bool no_label = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoLabel", &no_label);
    if (no_label)
    {
        options |= ImGuiGradientFlags_NoLabel;
    }
    static bool no_random_mode = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoRandomModeChange", &no_random_mode);
    if (no_random_mode)
    {
        options |= ImGuiGradientFlags_NoRandomModeChange;
    }
    static bool no_add_button = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoAddButton", &no_add_button);
    if (no_add_button)
    {
        options |= ImGuiGradientFlags_NoAddButton;
    }
    static bool no_remove_button = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoRemoveButton", &no_remove_button);
    if (no_remove_button)
    {
        options |= ImGuiGradientFlags_NoRemoveButton;
    }
    static bool no_drag_slider = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoPositionSlider", &no_drag_slider);
    if (no_drag_slider)
    {
        options |= ImGuiGradientFlags_NoPositionSlider;
    }
    static bool no_color_edit = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoColorEdit", &no_color_edit);
    if (no_color_edit)
    {
        options |= ImGuiGradientFlags_NoColorEdit;
    }
    static bool no_posittion_mode_combo = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoPositionModeCombo", &no_posittion_mode_combo);
    if (no_posittion_mode_combo)
    {
        options |= ImGuiGradientFlags_NoPositionModeCombo;
    }
    static bool no_interpolation_combo = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoInterpolationCombo", &no_interpolation_combo);
    if (no_interpolation_combo)
    {
        options |= ImGuiGradientFlags_NoInterpolationCombo;
    }
    static bool no_drag_down_to_delete = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoDragDowntoDelete", &no_drag_down_to_delete);
    if (no_drag_down_to_delete)
    {
        options |= ImGuiGradientFlags_NoDragDowntoDelete;
    }
    static bool no_border = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoBorder", &no_border);
    if (no_border)
    {
        options |= ImGuiGradientFlags_NoBorder;
    }
    static bool no_add_and_remove_button = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoAddAndRemoveButton", &no_add_and_remove_button);
    if (no_add_and_remove_button)
    {
        options |= ImGuiGradientFlags_NoAddAndRemoveButton;
    }
    static bool no_mark_options = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoMarkOptions", &no_mark_options);
    if (no_mark_options)
    {
        options |= ImGuiGradientFlags_NoMarkOptions;
    }
    static bool no_combo = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoCombo", &no_combo);
    if (no_combo)
    {
        options |= ImGuiGradientFlags_NoCombo;
    }
    static bool no_combo_and_random_mode = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoComboAndRandomMode", &no_combo_and_random_mode);
    if (no_combo_and_random_mode)
    {
        options |= ImGuiGradientFlags_NoComboAndRandomMode;
    }
    static bool no_button_and_mark_options = false;
    ImGui::Checkbox("ImGuiGradientFlags_NoButtonAndMarkOptions", &no_button_and_mark_options);
    if (no_button_and_mark_options)
    {
        options |= ImGuiGradientFlags_NoButtonAndMarkOptions;
    }
    return options;
}