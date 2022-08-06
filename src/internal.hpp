#pragma once

#include <imgui/imgui.h>

namespace ImGuiGradient {

namespace internal {

inline auto button_height() -> float
{
    return ImGui::GetFrameHeight();
}

inline auto gradient_position(float x_offset) -> ImVec2
{
    return ImGui::GetCursorScreenPos() + ImVec2(x_offset, 0.f);
}

inline auto border_color() -> ImColor // TODO(ASG) Use ImU32
{
    return ImGui::GetColorU32(ImGuiCol_Border);
}

inline auto mark_color() -> ImColor
{
    return ImGui::GetColorU32(ImGuiCol_Button);
}

inline auto hovered_mark_color() -> ImColor
{
    return ImGui::GetColorU32(ImGuiCol_ButtonHovered);
}

inline auto selected_mark_color() -> ImColor
{
    return ImGui::GetColorU32(ImGuiCol_ButtonActive);
}

}} // namespace ImGuiGradient::internal