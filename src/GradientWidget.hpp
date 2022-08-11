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
    /// Only provides const access. Modifications should be done through this `GradientWidget` directly because we have invariants to maintain.
    auto get_gradient() const -> const Gradient&;

    void add_mark(float position);
    void add_mark(float position, std::default_random_engine& generator);

    void remove_mark(const Mark& mark);

    void set_mark_position(const Mark& mark, RelativePosition position);
    void set_mark_color(const Mark& mark, ColorRGBA color);
    void set_wrap_mode(WrapMode new_wrap_mode);
    void set_interpolation_mode(Interpolation new_interpolation_mode);
    void enable_random_color_mode(bool is_random_enable);

    void reset();

    auto widget(
        const char*                 label,
        const Settings&             settings,
        std::default_random_engine& generator
    ) -> bool;
    auto widget(
        const char*     label,
        const Settings& settings
    ) -> bool;

private:
    auto draw_gradient_marks(
        const Mark*   mark_to_delete,
        const ImVec2& gradient_bar_pos,
        ImVec2        size
    ) -> bool;
    auto mouse_dragging_interactions(
        ImVec2          gradient_bar_position,
        ImVec2          gradient_size,
        const Settings& settings
    ) -> bool;

private:
    internal::State state{};
    WrapMode        wrap_mode{WrapMode::Clamp};
    Interpolation   interpolation_mode{Interpolation::Linear};
    bool            should_use_a_random_color_for_the_new_marks{false};
};

} // namespace ImGuiGradient