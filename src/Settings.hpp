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
    float distance_to_delete_mark_by_dragging_down = 80.f;
    /// Offset between right beginning of the window and gradient bar beginning
    float horizontal_margin = 10.f;
    /// Disable or enable gradient widget options
    ImGuiGradient::Flags flags = ImGuiGradient::Flag::None;
    /// Change color picker behaviour
    ImGuiColorEditFlags color_flags = ImGuiColorEditFlags_None;
    /// Controls how a mark position that is outside of the [0, 1] range is mapped back into that range.
    WrapMode wrap_mode{WrapMode::Clamp};
    /// Controls how the colors are interpolated between two marks.
    Interpolation interpolation_mode{Interpolation::Linear};
    /// Controls how the new mark color is chosen.
    /// If `should_use_a_random_color_for_the_new_marks` is enable the new mark color will be a random color,
    /// else it will be the one wich is computed at the mark position.
    bool should_use_a_random_color_for_the_new_marks{false};
};

} // namespace ImGuiGradient