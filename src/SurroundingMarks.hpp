#pragma once

#include "Mark.hpp"

namespace ImGuiGradient {

namespace internal {

struct SurroundingMarks {
    const Mark* lower{nullptr};
    const Mark* upper{nullptr};
};

}} // namespace ImGuiGradient::internal