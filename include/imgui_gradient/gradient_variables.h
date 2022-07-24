#pragma once

#include <random>

namespace variables {
static constexpr float GRADIENT_BAR_WIDGET_HEIGHT = 25.f;
static constexpr float GRADIENT_BAR_EDITOR_HEIGHT = 40.f;
static constexpr float GRADIENT_MARK_DELETE_DIFFY = 40.f;

float rand() // TODO(ASG) the user could choose the generator
{
    static std::default_random_engine     generator{std::random_device{}()};
    std::uniform_real_distribution<float> distribution{0.f, 1.f};
    return distribution(generator);
}

static auto random_color() -> ImVec4
{
    const auto color = ImVec4{variables::rand(), variables::rand(), variables::rand(), 1.f};
    return color;
}

static auto button_size() -> float
{
    return ImGui::GetFrameHeight();
}

static auto bar_position(const float offset) -> ImVec2
{
    return ImGui::GetCursorScreenPos() + ImVec2(offset, 0.f);
}

static auto empty_backgroung_color() -> ImU32
{
    return IM_COL32(0, 0, 0, 255);
}

static auto border_color() -> ImU32
{
    return IM_COL32(100, 100, 100, 255);
}

static auto inside_arrow_border_color() -> ImU32
{
    return IM_COL32(0, 0, 0, 255);
}

static auto selected_mark_color() -> ImU32
{
    return IM_COL32(0, 255, 0, 255);
}

} // namespace variables
