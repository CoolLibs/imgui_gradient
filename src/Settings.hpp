#pragma once

#include "Flags.hpp"

namespace ImGuiGradient {

struct Settings {
    float                gradient_height                          = 25.f;
    float                gradient_editor_height                   = 40.f; // TODO(ASG) Rename as widget_height. // TODO(ASG) What does that do???
    float                distance_to_delete_mark_by_dragging_down = 40.f; // This behaviour can also be disabled with the Flag::NoDragDowntoDelete
    float                horizontal_margin                        = 10.f;
    ImGuiGradient::Flags flags                                    = ImGuiGradient::Flag::None;
    ImGuiColorEditFlags  color_flags                              = ImGuiColorEditFlags_None;
};

} // namespace ImGuiGradient