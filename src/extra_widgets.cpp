#include "extra_widgets.hpp"
#include <imgui/imgui.h>
#include <array>
#include "imgui_internal.hpp"
#include "tooltip.hpp"

namespace ImGuiGradient {

template<size_t size>
static auto selector_with_tooltip(
    const char*                          label,
    size_t&                              current_item_index,
    const std::array<const char*, size>& items,
    const char*                          longuest_item_name, // Use the longuest word to choose the selector's size
    const std::array<const char*, size>& tooltips,
    const bool                           should_show_tooltip
) -> bool
{
    ImGuiContext& g{*GImGui};
    const auto    width{
        ImGui::CalcTextSize(longuest_item_name).x +
        ImGui::GetFrameHeightWithSpacing() +
        g.Style.FramePadding.x * 2.f};
    ImGui::SetNextItemWidth(width);

    auto modified{false};
    auto combo_preview_value{items[current_item_index]};

    if (ImGui::BeginCombo(label, combo_preview_value))
    {
        for (size_t n = 0; n < items.size(); n++)
        {
            const bool is_selected{(current_item_index == n)};
            if (ImGui::Selectable(items[n], is_selected))
            {
                current_item_index = n;
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

auto random_mode_checkbox(
    const char* label,
    bool&       should_use_a_random_color_for_the_new_marks,
    const bool  should_show_tooltip
) -> bool
{
    const bool modified = ImGui::Checkbox(
        label,
        &should_use_a_random_color_for_the_new_marks
    );
    if (should_show_tooltip)
    {
        tooltip("Add mark with random color");
    }
    return modified;
}

auto wrap_mode_selector(const char* label, WrapMode& wrap_mode, const bool should_show_tooltip) -> bool
{
    const std::array<const char*, 3> items    = {"Clamp", "Repeat", "Mirror Repeat"};
    const std::array<const char*, 3> tooltips = {
        "Clamp mark position in range [0.,1.]",
        "Repeat mark position in range [0.,1.]",
        "Repeat and mirror mark position in range [0.,1.]"};

    return selector_with_tooltip(
        label,
        reinterpret_cast<size_t&>(wrap_mode),
        items,
        "Mirror Repeat",
        tooltips,
        should_show_tooltip
    );
}

auto gradient_interpolation_mode_selector(const char* label, Interpolation& interpolation_mode, const bool should_show_tooltip) -> bool
{
    const std::array<const char*, 2> items    = {"Linear", "Constant"};
    const std::array<const char*, 2> tooltips = {
        "Linear interpolation between two marks",
        "Constant color between two marks"};

    return selector_with_tooltip(
        label,
        reinterpret_cast<size_t&>(interpolation_mode),
        items,
        "Constant",
        tooltips,
        should_show_tooltip
    );
}
} // namespace ImGuiGradient