#pragma once

#include "Interpolation.hpp"
#include "WrapMode.hpp"

namespace ImGuiGradient {

auto random_mode_checkbox(
    const char* label,
    bool&       should_use_a_random_color_for_the_new_marks,
    bool        should_show_tooltip = true
) -> bool;

auto wrap_mode_selector(
    const char* label,
    WrapMode&   wrap_mode,
    bool        should_show_tooltip = true
) -> bool;

auto gradient_interpolation_mode_selector(
    const char*    label,
    Interpolation& interpolation_mode,
    bool           should_show_tooltip = true
) -> bool;

} // namespace ImGuiGradient