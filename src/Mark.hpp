#pragma once

#include <imgui/imgui.h> // Include ImVec4

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui_internal.h>
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#include "RelativePosition.hpp"

namespace ImGuiGradient {

using ColorRGBA = ImVec4;

inline auto operator==(const ColorRGBA& a, const ColorRGBA& b) -> bool
{
    return (a.x == b.x) &&
           (a.y == b.y) &&
           (a.z == b.z) &&
           (a.w == b.w);
}

struct Mark {
    RelativePosition position{0.f};
    ColorRGBA        color{0.f, 0.f, 0.f, 1.f};

    friend auto operator==(const Mark& a, const Mark& b) -> bool
    {
        return (a.position == b.position) &&
               (a.color == b.color);
    };
};

} // namespace ImGuiGradient