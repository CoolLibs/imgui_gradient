#pragma once

#include <imgui/imgui.h>
#include "Flags.hpp"

namespace ImGuiGradient {

struct Settings {
    float gradient_height{40.f};
    /// Distance under the gradient bar to delete a mark by dragging it down.
    /// This behaviour can also be disabled with the Flag::NoDragDowntoDelete.
    float                distance_to_delete_mark_by_dragging_down{80.f};
    float                horizontal_margin{10.f};
    ImGuiGradient::Flags flags{ImGuiGradient::Flag::None};
    ImGuiColorEditFlags  color_edit_flags{ImGuiColorEditFlags_None};
    /// Controls how the colors are interpolated between two marks.
    Interpolation interpolation_mode{Interpolation::Linear};
    /// Controls how the new mark color is chosen.
    /// If `should_use_a_random_color_for_the_new_marks` is enabled the new mark color will be a random color,
    /// else it will be the one that the gradient already has before at the mark position.
    bool should_use_a_random_color_for_the_new_marks{false};
};

} // namespace ImGuiGradient