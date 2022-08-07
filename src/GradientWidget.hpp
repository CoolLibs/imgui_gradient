// Inspired by https://gist.github.com/galloscript/8a5d179e432e062550972afcd1ecf112

// TODO(ASG) Documentation

#pragma once

#include <random>
#include "Flags.hpp"
#include "Interpolation.hpp"
#include "Settings.hpp"
#include "State.hpp"
#include "WrapMode.hpp"

namespace ImGuiGradient {

class GradientWidget {
public:
    GradientWidget() = default;
    auto get_gradient() const -> const Gradient& { return state.gradient; }
    auto add_mark(float position) -> bool;
    auto add_mark(float position, std::default_random_engine& generator) -> bool;

    auto widget(const char* label, std::default_random_engine& generator, const Settings& settings) -> bool;
    auto widget(const char* label, const Settings& settings) -> bool;

private:
    auto draw_gradient_marks(const Mark* mark_to_delete, const ImVec2& gradient_bar_pos, ImVec2 size) -> bool;
    auto mouse_dragging(float gradient_bar_bottom, float width, float gradient_bar_pos_x, const Settings& settings) -> bool;

private:
    internal::State state{};
    WrapMode        wrap_mode{WrapMode::Clamp};
    Interpolation   interpolation_mode{Interpolation::Linear};
    bool            should_use_a_random_color_for_the_new_marks{false};
};

} // namespace ImGuiGradient