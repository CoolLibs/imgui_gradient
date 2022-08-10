#pragma once

#include <imgui/imgui.h> // Include ImVec4

namespace ImGuiGradient {

using ColorRGBA = ImVec4;

inline auto operator==(const ColorRGBA& a, const ColorRGBA& b) -> bool
{
    return (a.x == b.x) &&
           (a.y == b.y) &&
           (a.z == b.z) &&
           (a.w == b.w);
}

} // namespace ImGuiGradient