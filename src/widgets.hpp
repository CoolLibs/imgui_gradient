#pragma once

#include <imgui/imgui.h>

namespace ImGuiGradient {

void button_disabled(const char* label, const char* reason_for_disabling, ImVec2 size);
void button_disabled(const char* label, const char* reason_for_disabling);

}; // namespace ImGuiGradient