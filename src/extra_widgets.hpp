#pragma once

#include "Interpolation.hpp"
#include "WrapMode.hpp"

namespace ImGuiGradient {

auto random_mode_box(
    const char* label,
    bool&       should_use_a_random_color_for_the_new_marks,
    const bool  should_show_tooltip
) -> bool;
auto wrap_mode_selector(
    const char* label,
    WrapMode&   wrap_mode,
    const bool  should_show_tooltip
) -> bool;
auto gradient_interpolation_mode_selector(
    const char*    label,
    Interpolation& interpolation_mode,
    const bool     should_show_tooltip
) -> bool;

} // namespace ImGuiGradient