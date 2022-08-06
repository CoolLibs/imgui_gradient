#pragma once

#include "Flags.hpp"

// TODO(ASG) Rename this file as Settings
namespace ImGuiGradient {

struct Settings {
    float                gradient_height            = 25.f;
    float                gradient_editor_height     = 40.f;
    float                gradient_mark_delete_diffy = 40.f; // TODO(ASG) Document what his does, and find a better name
    float                horizontal_margin          = 10.f;
    ImGuiGradient::Flags flags                      = Flag::None;
    ImGuiColorEditFlags  color_flags                = ImGuiColorEditFlags_None;
};

// TODO(ASG) The things below don't belong to this File
namespace internal {

inline auto button_size() -> float // TODO(ASG) Should be named button_height
{
    return ImGui::GetFrameHeight();
}

inline auto gradient_position(float offset) -> ImVec2 // TODO(ASG) offset should be named x_offset
{
    return ImGui::GetCursorScreenPos() + ImVec2(offset, 0.f);
}

inline auto color__border() -> ImU32 // TODO(ASG) acutally I don't like this name, border_color is better
{
    return ImGui::GetColorU32(ImGuiCol_Border);
}

inline auto color__mark() -> ImU32 // TODO(ASG)same
{
    return ImGui::GetColorU32(ImGuiCol_Button);
}

inline auto color__hovered_mark() -> ImU32 // TODO(ASG) same
{
    return ImGui::GetColorU32(ImGuiCol_ButtonHovered);
}

inline auto color__selected_mark() -> ImU32 // TODO(ASG) same
{
    return ImGui::GetColorU32(ImGuiCol_ButtonActive);
}

} // namespace internal

} // namespace ImGuiGradient