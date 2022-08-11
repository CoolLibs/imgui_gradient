#pragma once

#include "Mark.hpp"

namespace ImGuiGradient { namespace internal {

struct SurroundingMarks {
    SurroundingMarks(const Mark* lower, const Mark* upper) // Need it to compile with MacOS Clang
        : lower(lower), upper(upper){};
    const Mark* lower{nullptr};
    const Mark* upper{nullptr};
};

}} // namespace ImGuiGradient::internal