#pragma once

#include "Flags.hpp"

namespace ImGuiGradient {

struct Settings {
    float                gradient_height            = 25.f;
    float                gradient_editor_height     = 40.f;
    float                gradient_mark_delete_diffy = 40.f; // TODO(ASG) Document what his does, and find a better name
    float                horizontal_margin          = 10.f;
    ImGuiGradient::Flags flags                      = Flag::None;
    ImGuiColorEditFlags  color_flags                = ImGuiColorEditFlags_None;
};

} // namespace ImGuiGradient