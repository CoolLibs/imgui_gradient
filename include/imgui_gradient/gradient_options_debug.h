#pragma once

#include <imgui/imgui.h>
#include "GradientOptions.h"

// TODO(ASG) unwanted behaviour when "+" and "-" button does not exists
// TODO(ASG) often when dragging a mark a black line appears

auto gradient_options_debug() -> GradientOptions
{
    GradientOptions options = GradientOptions_None;

    static bool none = false;
    ImGui::Checkbox("GradientOptions_None", &none);
    if (none)
    {
        options |= GradientOptions_None;
    }
    static bool no_tool_tip = false;
    ImGui::Checkbox("GradientOptions_NoTooltip", &no_tool_tip);
    if (no_tool_tip)
    {
        options |= GradientOptions_NoTooltip;
    }
    static bool no_reset_button = false;
    ImGui::Checkbox("GradientOptions_NoResetButton", &no_reset_button);
    if (no_reset_button)
    {
        options |= GradientOptions_NoResetButton;
    }
    static bool no_label = false;
    ImGui::Checkbox("GradientOptions_NoLabel", &no_label);
    if (no_label)
    {
        options |= GradientOptions_NoLabel;
    }
    static bool no_random_mode = false;
    ImGui::Checkbox("GradientOptions_NoRandomMode", &no_random_mode);
    if (no_random_mode)
    {
        options |= GradientOptions_NoRandomMode;
    }
    static bool no_add_button = false;
    ImGui::Checkbox("GradientOptions_NoAddButton", &no_add_button);
    if (no_add_button)
    {
        options |= GradientOptions_NoAddButton;
    }
    static bool no_remove_button = false;
    ImGui::Checkbox("GradientOptions_NoRemoveButton", &no_remove_button);
    if (no_remove_button)
    {
        options |= GradientOptions_NoRemoveButton;
    }
    static bool no_drag_slider = false;
    ImGui::Checkbox("GradientOptions_NoDragSlider", &no_drag_slider);
    if (no_drag_slider)
    {
        options |= GradientOptions_NoDragSlider;
    }
    static bool no_color_edit = false;
    ImGui::Checkbox("GradientOptions_NoColorEdit", &no_color_edit);
    if (no_color_edit)
    {
        options |= GradientOptions_NoColorEdit;
    }
    static bool no_posittion_mode_combo = false;
    ImGui::Checkbox("GradientOptions_NoPositionModeCombo", &no_posittion_mode_combo);
    if (no_posittion_mode_combo)
    {
        options |= GradientOptions_NoPositionModeCombo;
    }
    static bool no_interpolation_combo = false;
    ImGui::Checkbox("GradientOptions_NoInterpolationCombo", &no_interpolation_combo);
    if (no_interpolation_combo)
    {
        options |= GradientOptions_NoInterpolationCombo;
    }
    static bool no_drag_down_to_delete = false;
    ImGui::Checkbox("GradientOptions_NoDragDowntoDelete", &no_drag_down_to_delete);
    if (no_drag_down_to_delete)
    {
        options |= GradientOptions_NoDragDowntoDelete;
    }
    static bool no_border = false;
    ImGui::Checkbox("GradientOptions_NoBorder", &no_border);
    if (no_border)
    {
        options |= GradientOptions_NoBorder;
    }
    static bool no_add_and_remove_button = false;
    ImGui::Checkbox("GradientOptions_NoAddAndRemoveButton", &no_add_and_remove_button);
    if (no_add_and_remove_button)
    {
        options |= GradientOptions_NoAddAndRemoveButton;
    }
    static bool no_mark_options = false;
    ImGui::Checkbox("GradientOptions_NoMarkOptions", &no_mark_options);
    if (no_mark_options)
    {
        options |= GradientOptions_NoMarkOptions;
    }
    static bool no_combo = false;
    ImGui::Checkbox("GradientOptions_NoCombo", &no_combo);
    if (no_combo)
    {
        options |= GradientOptions_NoCombo;
    }
    static bool no_combo_and_random_mode = false;
    ImGui::Checkbox("GradientOptions_NoComboAndRandomMode", &no_combo_and_random_mode);
    if (no_combo_and_random_mode)
    {
        options |= GradientOptions_NoComboAndRandomMode;
    }
    static bool no_button_and_mark_options = false;
    ImGui::Checkbox("GradientOptions_NoButtonAndMarkOptions", &no_button_and_mark_options);
    if (no_button_and_mark_options)
    {
        options |= GradientOptions_NoButtonAndMarkOptions;
    }
    return options;
}