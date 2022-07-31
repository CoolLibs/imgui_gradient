#pragma once

#include <imgui/imgui.h>
#include <cassert>
#include "Interpolation.h"
#include "PositionMode.h"


namespace ImGuiGradient {

bool position_mode_combo(PositionMode& position_mode)
{
    int current_combo_item = [&]() {
        switch (position_mode)
        {
        case PositionMode::clamp:
            return 0;
        case PositionMode::repeat:
            return 1;
        case PositionMode::mirror_clamp:
            return 2;
        case PositionMode::mirror_repeat:
            return 3;
        default:
            assert(false);
            return -1;
        }
    }();
    const char* position_mode_items = " Clamp\0 Repeat\0 Mirror Clamp\0 Mirror Repeat\0\0";
    if (ImGui::Combo("Position Mode", &current_combo_item, position_mode_items))
    {
        switch (current_combo_item)
        {
        case 0:
            position_mode = PositionMode::clamp;
            break;
        case 1:
            position_mode = PositionMode::repeat;
            break;
        case 2:
            position_mode = PositionMode::mirror_clamp;
            break;
        case 3:
            position_mode = PositionMode::mirror_repeat;
            break;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool gradient_interpolation_mode(Interpolation& interpolation_mode)
{
    int current_combo_item = [&]() {
        switch (interpolation_mode)
        {
        case Interpolation::linear:
            return 0;
        case Interpolation::constant:
            return 1;
        default:
            assert(false);
            return 0;
        }
    }();
    const char* interpolation_mode_items = " Linear\0 Constant\0\0";
    if (ImGui::Combo("Interpolation Mode", &current_combo_item, interpolation_mode_items))
    {
        switch (current_combo_item)
        {
        case 0:
            interpolation_mode = Interpolation::linear;
            break;
        case 1:
            interpolation_mode = Interpolation::constant;
            break;
        }
        return true;
    }
    else
    {
        return false;
    }
}

void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text);
        ImGui::EndTooltip();
    }
}

} // namespace ImGuiGradient