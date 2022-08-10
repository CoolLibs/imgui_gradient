#pragma once

#include <imgui/imgui.h>
#include "Flags.hpp"

namespace ImGuiGradient {

/// Parameters that uses gradient widget to display itself
struct Settings {
    /// Gradient bar size on y axis
    float gradient_height = 40.f;
    /// Distance under the gradient bar to delete a mark by dragging it down
    /// This behaviour can also be disabled with the Flag::NoDragDowntoDelete
    float distance_to_delete_mark_by_dragging_down = 40.f;
    /// Offset between right beginning of the window and gradient bar beginning
    float horizontal_margin = 10.f;
    /// Disable or enable gradient widget options
    ImGuiGradient::Flags flags = ImGuiGradient::Flag::None;
    /// Change color picker behaviour
    ImGuiColorEditFlags color_flags = ImGuiColorEditFlags_None;
};

} // namespace ImGuiGradient