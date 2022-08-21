#pragma once

#include <imgui/imgui.h>

namespace ImGG {

void button_disabled(const char* label, const char* reason_for_disabling, ImVec2 size = ImVec2(0, 0));

}; // namespace ImGG