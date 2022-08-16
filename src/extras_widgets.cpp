#include "extras_widgets.hpp"
#include <imgui/imgui.h>
#include <array>
#include "imgui_internal.hpp"
#include "tooltip.hpp"

namespace ImGuiGradient {

template<size_t size>
static auto selector_with_tooltip(
    const char*                         label,
    int&                                item_current_index,
    const std::array<const char*, size> items,
    const char*                         greater_items, // Use the longuest word to choose the selector's size
    const std::array<const char*, size> tooltips,
    const bool                          should_show_tooltip
) -> bool
{
    ImGuiContext& g{*GImGui};
    const auto    width{
        ImGui::CalcTextSize(greater_items).x +
        ImGui::GetFrameHeightWithSpacing() +
        g.Style.FramePadding.x * 2.f};
    ImGui::SetNextItemWidth(width);

    auto        modified{false};                                                     // Here we store our selection data as an index.
    const char* combo_preview_value{items[static_cast<size_t>(item_current_index)]}; // Pass in the preview value visible before opening the combo (it could be anything)
    if (ImGui::BeginCombo(label, combo_preview_value))
    {
        for (size_t n = 0; n < items.size(); n++)
        {
            const bool is_selected{(item_current_index == n)};
            if (ImGui::Selectable(items[n], is_selected))
            {
                item_current_index = static_cast<int>(n);
                modified           = true;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
            if (should_show_tooltip)
            {
                tooltip(tooltips[n]);
            }
        }
        ImGui::EndCombo();
    }
    return modified;
}

auto random_mode_box(
    bool&      should_use_a_random_color_for_the_new_marks,
    const bool should_show_tooltip
) -> bool
{
    const bool modified = ImGui::Checkbox(
        "Random Mode",
        &should_use_a_random_color_for_the_new_marks
    );
    if (should_show_tooltip)
    {
        tooltip("Add mark with random color");
    }
    return modified;
}

auto wrap_mode_selector(WrapMode& wrap_mode, const bool should_show_tooltip) -> bool
{
    const std::array<const char*, 3> items    = {"Clamp", "Repeat", "Mirror Repeat"};
    const std::array<const char*, 3> tooltips = {
        "Clamp mark position in range [0.,1.]",
        "Repeat mark position in range [0.,1.]",
        "Repeat and mirror mark position in range [0.,1.]"};

    return selector_with_tooltip(
        "Position Mode",
        reinterpret_cast<int&>(wrap_mode),
        items,
        "Mirror Repeat",
        tooltips,
        should_show_tooltip
    );
}

auto gradient_interpolation_mode_selector(Interpolation& interpolation_mode, const bool should_show_tooltip) -> bool
{
    const std::array<const char*, 2> items    = {"Linear", "Constant"};
    const std::array<const char*, 2> tooltips = {
        "Linear interpolation between two marks",
        "Constant color between two marks"};

    return selector_with_tooltip(
        "Interpolation Mode",
        reinterpret_cast<int&>(interpolation_mode),
        items,
        "Constant",
        tooltips,
        should_show_tooltip
    );
}
} // namespace ImGuiGradient