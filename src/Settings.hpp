#pragma once

#include "Flags.hpp"

namespace ImGuiGradient {

struct Settings {
    float                gradient_height                          = 25.f;
    float                gradient_editor_height                   = 40.f;
    float                delete_mark_by_dragging_down_sensibility = 40.f; // Difference on the y axis between the position of the gradient and the position of removing a mark by dragging it down
    float                horizontal_margin                        = 10.f;
    ImGuiGradient::Flags flags                                    = Flag::None;
    ImGuiColorEditFlags  color_flags                              = ImGuiColorEditFlags_None;
};

} // namespace ImGuiGradient