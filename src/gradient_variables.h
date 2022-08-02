#pragma once

namespace ImGuiGradient {

// struct Settings {
//  float gradient_height           = 25.f;
//  float gradient_editor_height    = 40.f;
//  float gradient_mak_delete_diffy = 40.f;
//     GradientOptions flags;
// };

namespace internal {

static constexpr float gradient_height           = 25.f;
static constexpr float gradient_editor_height    = 40.f;
static constexpr float gradient_mak_delete_diffy = 40.f;

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
    return IM_COL32(100, 100, 100, 255); // TODO(ASG) Use ImGui's color from the theme (ImGui::GetStyleColorVec4(ImGuiCol_NavHighlight);) Don't use GetStyleColorVec4, use the one that returns a IM_COL32 directly
}

inline auto color__inside_arrow_border() -> ImU32
{
    return IM_COL32(0, 0, 0, 255);
}

inline auto color__selected_mark() -> ImU32
{
    return IM_COL32(0, 255, 0, 255);
}

} // namespace internal

} // namespace ImGuiGradient