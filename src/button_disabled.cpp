#include "button_disabled.hpp"
#include <functional>
#include "tooltip.hpp"

namespace ImGuiGradient {

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

} // namespace ImGuiGradient