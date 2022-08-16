#pragma once

#include "Gradient.hpp"
#include "MarkId.hpp"

namespace ImGuiGradient { namespace internal {

struct State {
    Gradient gradient{};
    MarkId   dragged_mark{nullptr};
    MarkId   selected_mark{nullptr};
    MarkId   mark_to_hide{nullptr};
};

}} // namespace ImGuiGradient::internal