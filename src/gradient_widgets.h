#pragma once

#include <imgui/imgui.h>
#include <cassert>
#include <string_view>
#include "Gradient.h"
#include "GradientOptions.h"
#include "Interpolation.h"
#include "PositionMode.h"
#include "gradient_variables.h"

namespace ImGuiGradient {

void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text);
        ImGui::EndTooltip();
    }
}

auto button(std::string_view name, std::string_view tooltip_message, ImVec2 size = ImVec2{0.f, 0.f}, GradientOptions options = GradientOptions_None) -> bool
{
    const bool clicked = ImGui::Button(name.data(), size);
    if (!(options & GradientOptions_NoTooltip))
    {
        tooltip(tooltip_message.data());
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

auto delete_button(const float size, GradientOptions options = GradientOptions_None) -> bool
{
    return button(
        "-",
        "Select a mark to remove it\nor middle click on it\nor drag it down",
        ImVec2{size, size},
        options
    );
}

auto add_button(const float size, GradientOptions options = GradientOptions_None) -> bool
{
    return button(
        "+",
        "Add a mark here\nor click on the gradient to choose its position",
        ImVec2{size, size},
        options
    );
}

auto color_button(Mark* selected_mark, GradientOptions options = GradientOptions_None, ImGuiColorEditFlags flags = 0) -> bool
{
    return (selected_mark && ImGui::ColorEdit4("##picker1", reinterpret_cast<float*>(&selected_mark->color), !(options & GradientOptions_NoTooltip) ? ImGuiColorEditFlags_NoInputs | flags : ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | flags));
}

auto precise_position(Gradient gradient, Mark* selected_mark, const float width, GradientOptions options = GradientOptions_None) -> bool
{
    bool modified = false;
    ImGui::PushItemWidth(width * .25f);
    if (selected_mark)
    {
        const float speed = 1.f / width;
        if (ImGui::DragFloat("##3", &selected_mark->get_position(), speed, 0.f, 1.f, "%.3f", ImGuiSliderFlags_AlwaysClamp))
        {
            gradient.get_marks().sort();
            modified = true;
        }
        if (!gradient.is_empty() && !(options & GradientOptions_NoTooltip))
        {
            tooltip("Choose a precise position");
        }
    }
    return modified;
}

auto random_mode_box(bool& random_mode, GradientOptions options = GradientOptions_None) -> bool
{
    const bool activate = ImGui::Checkbox("Random Mode", &random_mode);
    if (!(options & GradientOptions_NoTooltip))
    {
        tooltip("Add mark with random color");
    }
    return activate;
}


auto popup(Mark* selected_mark, const float item_size, GradientOptions options = GradientOptions_None, ImGuiColorEditFlags flags = 0) -> bool
{
    const float popup_size = item_size * 12.f;
    if (ImGui::BeginPopup("picker") && selected_mark)
    {
        ImGui::SetNextItemWidth(popup_size);
        const bool modified = ImGui::ColorPicker4("##picker2", reinterpret_cast<float*>(&selected_mark->color), !(options & GradientOptions_NoTooltip) ? flags : ImGuiColorEditFlags_NoTooltip | flags);
        ImGui::EndPopup();
        return modified;
    }
    else
    {
        return false;
    }
}

} // namespace ImGuiGradient