/* -----------------------------------------------------------------------------
 * This file was automatically generated by a Python script.
 * PLEASE DON'T EDIT IT DIRECTLY, your changes would be overwritten the next time the script is run.
 * Instead, go to "generate_flags_checkbox.py" and edit the "checkboxes_for_all_flags" function there.
 * -----------------------------------------------------------------------------
 */

#include <imgui/imgui.h>
#include "../src/Flags.hpp"

auto checkboxes_for_all_flags() -> ImGG::Flags
{
    ImGG::Flags options = ImGG::Flag::None;

    static auto isNoTooltip = false;
    ImGui::Checkbox("ImGG::Flag::NoTooltip", &isNoTooltip);
    if (isNoTooltip)
    {
        options |= ImGG::Flag::NoTooltip;
    }

    static auto isNoResetButton = false;
    ImGui::Checkbox("ImGG::Flag::NoResetButton", &isNoResetButton);
    if (isNoResetButton)
    {
        options |= ImGG::Flag::NoResetButton;
    }

    static auto isNoLabel = false;
    ImGui::Checkbox("ImGG::Flag::NoLabel", &isNoLabel);
    if (isNoLabel)
    {
        options |= ImGG::Flag::NoLabel;
    }

    static auto isNoAddButton = false;
    ImGui::Checkbox("ImGG::Flag::NoAddButton", &isNoAddButton);
    if (isNoAddButton)
    {
        options |= ImGG::Flag::NoAddButton;
    }

    static auto isNoRemoveButton = false;
    ImGui::Checkbox("ImGG::Flag::NoRemoveButton", &isNoRemoveButton);
    if (isNoRemoveButton)
    {
        options |= ImGG::Flag::NoRemoveButton;
    }

    static auto isNoPositionSlider = false;
    ImGui::Checkbox("ImGG::Flag::NoPositionSlider", &isNoPositionSlider);
    if (isNoPositionSlider)
    {
        options |= ImGG::Flag::NoPositionSlider;
    }

    static auto isNoColorEdit = false;
    ImGui::Checkbox("ImGG::Flag::NoColorEdit", &isNoColorEdit);
    if (isNoColorEdit)
    {
        options |= ImGG::Flag::NoColorEdit;
    }

    static auto isNoDragDownToDelete = false;
    ImGui::Checkbox("ImGG::Flag::NoDragDownToDelete", &isNoDragDownToDelete);
    if (isNoDragDownToDelete)
    {
        options |= ImGG::Flag::NoDragDownToDelete;
    }

    static auto isNoBorder = false;
    ImGui::Checkbox("ImGG::Flag::NoBorder", &isNoBorder);
    if (isNoBorder)
    {
        options |= ImGG::Flag::NoBorder;
    }

    static auto isNoAddAndRemoveButtons = false;
    ImGui::Checkbox("ImGG::Flag::NoAddAndRemoveButtons", &isNoAddAndRemoveButtons);
    if (isNoAddAndRemoveButtons)
    {
        options |= ImGG::Flag::NoAddAndRemoveButtons;
    }

    static auto isNoMarkOptions = false;
    ImGui::Checkbox("ImGG::Flag::NoMarkOptions", &isNoMarkOptions);
    if (isNoMarkOptions)
    {
        options |= ImGG::Flag::NoMarkOptions;
    }

    return options;
}