# ---HOW TO---
# Modify `all_flags()` and `includes()`, then run this script.
# ------------


def all_flags():
    return {
        "ImGuiGradient::Flag::None":                       ["isNone"],
        "ImGuiGradient::Flag::NoTooltip":                  ["isNoTooltip"],
        "ImGuiGradient::Flag::NoResetButton":              ["isNoResetButton"],
        "ImGuiGradient::Flag::NoLabel":                    ["isNoLabel"],
        "ImGuiGradient::Flag::NoRandomModeCheckBox":       ["isNoRandomModeCheckBox"],
        "ImGuiGradient::Flag::NoAddButton":                ["isNoAddButton"],
        "ImGuiGradient::Flag::NoRemoveButton":             ["isNoRemoveButton"],
        "ImGuiGradient::Flag::NoPositionSlider":           ["isNoPositionSlider"],
        "ImGuiGradient::Flag::NoColorEdit":                ["isNoColorEdit"],
        "ImGuiGradient::Flag::NoWrapModeSelector":         ["isNoWrapModeSelector"],
        "ImGuiGradient::Flag::NoInterpolationSelector":    ["isNoInterpolationSelector"],
        "ImGuiGradient::Flag::NoDragDownToDelete":         ["isNoDragDownToDelete"],
        "ImGuiGradient::Flag::NoBorder":                   ["isNoBorder"],
        "ImGuiGradient::Flag::NoAddAndRemoveButtons":      ["isNoAddAndRemoveButtons"],
        "ImGuiGradient::Flag::NoMarkOptions":              ["isNoMarkOptions"],
        "ImGuiGradient::Flag::NoSelector":                 ["isNoSelector"],
    }

def checkboxes_for_all_flags():
    out = f"""
#include <imgui/imgui.h>
#include "../src/Flags.hpp"

auto checkboxes_for_all_flags() -> ImGuiGradient::Flags
{{
ImGuiGradient::Flags options = ImGuiGradient::Flag::None;

"""
    for key, values in all_flags().items():
        for value in values:
            out += f"""
static auto {value} = false;
ImGui::Checkbox("{key}", &{value});
if ({value})
{{
    options|={key};
}}
"""
    out+= f"""
    return options;
}}"""
    return out


if __name__ == '__main__':
    from tooling.generate_files import generate
    generate(
        folder="generated",
        files=[
            checkboxes_for_all_flags,
        ],
    )
