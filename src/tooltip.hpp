#pragma once

#include <imgui/imgui.h>

namespace ImGuiGradient {

inline void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text);
        ImGui::EndTooltip();
    }
}

} // namespace ImGuiGradient