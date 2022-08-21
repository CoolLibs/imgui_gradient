// Inspired by https://gist.github.com/galloscript/8a5d179e432e062550972afcd1ecf112

// TODO(ASG) Documentation

#pragma once

#include <random>
#include "Gradient.hpp"
#include "MarkId.hpp"
#include "Settings.hpp"

namespace ImGG {

class GradientWidget {
public:
    GradientWidget() = default;
    explicit GradientWidget(const std::list<Mark>& marks)
        : _gradient{marks}
    {}

    auto gradient() const -> const Gradient& { return _gradient; }
    auto gradient() -> Gradient& { return _gradient; }

    auto widget(
        const char*     label,
        const Settings& settings = {}
    ) -> bool;

    /// If `_should_use_a_random_color_for_the_new_marks` is true when adding a new mark,
    /// `generator` is used to generate the random color of the new mark.
    /// There is an overload that doesn't need `generator` and use the default generator of this library if users don't want to provide one.
    auto widget(
        const char*                 label,
        std::default_random_engine& generator,
        const Settings&             settings = {}
    ) -> bool;

private:
    void add_mark_with_chosen_mode(RelativePosition relative_pos, std::default_random_engine& generator, bool add_a_random_color);

    auto draw_gradient_marks(
        MarkId& mark_to_delete,
        ImVec2  gradient_bar_pos,
        ImVec2  size
    ) -> bool;

    auto mouse_dragging_interactions(
        ImVec2          gradient_bar_position,
        ImVec2          gradient_size,
        const Settings& settings
    ) -> bool;

private:
    Gradient _gradient{};
    MarkId   _dragged_mark{};
    MarkId   _selected_mark{};
    MarkId   _mark_to_hide{};
};

} // namespace ImGG