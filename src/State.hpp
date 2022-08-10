#pragma once

#include "Gradient.hpp"

namespace ImGuiGradient { namespace internal {

struct State {
    Gradient gradient{};
    Mark*    dragged_mark{};
    Mark*    selected_mark{};
    Mark*    mark_to_hide{};
};

}} // namespace ImGuiGradient::internal