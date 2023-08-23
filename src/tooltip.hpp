#pragma once

#include <imgui.h>

namespace ImGG {

inline void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(text);
        ImGui::EndTooltip();
    }
}

} // namespace ImGG