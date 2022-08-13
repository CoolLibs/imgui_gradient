#include "widgets.hpp"
#include <functional>

namespace ImGuiGradient {

static void tooltip(const char* text)
{
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::Text("%s", text);
        ImGui::EndTooltip();
    }
}

static void maybe_disabled(
    bool                  condition,
    const char*           reason_to_disable,
    std::function<void()> widgets
)
{
    if (condition)
    {
        ImGui::BeginGroup();
        ImGui::BeginDisabled(true);

        widgets();

        ImGui::EndDisabled();
        ImGui::EndGroup();
        tooltip(reason_to_disable);
    }
    else
    {
        ImGui::BeginGroup();

        widgets();

        ImGui::EndGroup();
    }
}

void button_disabled(const char* label, const char* reason_for_disabling, const ImVec2 size)
{
    maybe_disabled(true, reason_for_disabling, [&]() {
        ImGui::Button(label, size);
    });
}

void button_disabled(const char* label, const char* reason_for_disabling)
{
    maybe_disabled(true, reason_for_disabling, [&]() {
        ImGui::Button(label);
    });
}

} // namespace ImGuiGradient