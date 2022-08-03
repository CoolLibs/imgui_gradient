#pragma once

#include "Flags.hpp"

namespace ImGuiGradient {

struct Settings {
    float                gradient_height            = 25.f;
    float                gradient_editor_height     = 40.f;
    float                gradient_mark_delete_diffy = 40.f;
    float                horizontal_margin          = 10.f;
    ImGuiGradient::Flags flags                      = Flag::None;
    ImGuiColorEditFlags  color_flags                = ImGuiColorEditFlags_None;
};

namespace internal {

inline auto button_size() -> float
{
    return ImGui::GetFrameHeight();
}

inline auto gradient_position(float offset) -> ImVec2
{
    return ImGui::GetCursorScreenPos() + ImVec2(offset, 0.f);
}

inline auto color__border() -> ImU32
{
    return ImGui::GetColorU32(ImGuiCol_Border);
}

inline auto color__mark() -> ImU32
{
    return ImGui::GetColorU32(ImGuiCol_Button);
}

inline auto color__hovered_mark() -> ImU32
{
    return ImGui::GetColorU32(ImGuiCol_ButtonHovered);
}

inline auto color__selected_mark() -> ImU32
{
    return ImGui::GetColorU32(ImGuiCol_ButtonActive);
}

} // namespace internal

} // namespace ImGuiGradient