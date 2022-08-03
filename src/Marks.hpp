#pragma once

#include <imgui/imgui.h>
#include <list>

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

struct Mark {
    RelativePosition position{0.f};
    ImVec4           color{0.f, 0.f, 0.f, 1.f};

    Mark(RelativePosition position, ImVec4 color)
        : position{position}, color{color}
    {}
    auto   get_position() const -> float { return position.get(); }
    float& get_position() { return position.get(); }

    friend auto operator==(const Mark& a, const Mark& b) -> bool
    {
        return (a.position == b.position) &&
               (a.color.x == b.color.x) &&
               (a.color.y == b.color.y) &&
               (a.color.z == b.color.z) &&
               (a.color.w == b.color.w);
    };
};

} // namespace ImGuiGradient