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

struct Mark {
    RelativePosition position{0.f};
    ColorRGBA        color{0.f, 0.f, 0.f, 1.f};

    friend auto operator==(const Mark& a, const Mark& b) -> bool
    {
        return (a.position == b.position) &&
               (a.color.x == b.color.x) && // TODO(ASG) define an operator == for ColorRGBA
               (a.color.y == b.color.y) &&
               (a.color.z == b.color.z) &&
               (a.color.w == b.color.w);
    };
};

} // namespace ImGuiGradient