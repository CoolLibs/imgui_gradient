#include "maybe_disabled.hpp"
#include "tooltip.hpp"

namespace ImGG {

void maybe_disabled(
    bool                         condition,
    const char*                  reason_to_disable,
    std::function<void()> const& widgets
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

} // namespace ImGG