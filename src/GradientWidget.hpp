// Inspired by https://gist.github.com/galloscript/8a5d179e432e062550972afcd1ecf112

// TODO(ASG) Documentation

#pragma once

#include <random>
#include "Flags.hpp"
#include "Interpolation.hpp"
#include "MarkId.hpp"
#include "Settings.hpp"
#include "State.hpp"
#include "WrapMode.hpp"

namespace ImGuiGradient {

class GradientWidget {
public:
    auto gradient() const -> const Gradient& { return _state.gradient; }
    auto gradient() -> Gradient& { return _state.gradient; }

    void add_mark(float position);                                        // TODO(ASG) documentation to explain that this creates a mark with the color of the gradient at the `positions`
    void add_mark(float position, std::default_random_engine& generator); // TODO(ASG) This shouldn't have a generator. Users should be able to chose the color

    void set_wrap_mode(WrapMode new_wrap_mode);
    void set_interpolation_mode(Interpolation new_interpolation_mode);
    void set_random_color_mode(bool should_use_a_random_color_for_the_new_marks);

    auto is_valid(MarkId id) -> bool { return _state.gradient.find_ptr(id); }

    /// Resets the gradient to having just two marks: a black one at the beginning and a white one at the end.
    void reset();

    /// If `_should_use_a_random_color_for_the_new_marks` is true when adding a new mark,
    /// `generator` is used to generate the random color of the new mark.
    /// There is an overload that doesn't need `generator` and use the default generator of the library if users don't want to provide one.
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
    void add_mark_to_gradient(float position, std::default_random_engine generator);
    auto draw_gradient_marks(
        MarkId&       mark_to_delete,
        const ImVec2& gradient_bar_pos,
        ImVec2        size
    ) -> bool;
    auto mouse_dragging_interactions(
        ImVec2          gradient_bar_position,
        ImVec2          gradient_size,
        const Settings& settings
    ) -> bool;

private:
    internal::State _state{};
    WrapMode        _wrap_mode{WrapMode::Clamp};
    Interpolation   _interpolation_mode{Interpolation::Linear};
    bool            _should_use_a_random_color_for_the_new_marks{false};
};

} // namespace ImGuiGradient