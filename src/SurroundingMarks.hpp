#pragma once

#include "Mark.hpp"

namespace ImGuiGradient { namespace internal {

struct SurroundingMarks {
    SurroundingMarks(const Mark* lower, const Mark* upper) // We need to explicitly define the constructor in order to compile with MacOS Clang in C++ 11
        : lower{lower}
        , upper{upper}
    {}

    const Mark* lower{nullptr};
    const Mark* upper{nullptr};
};

}} // namespace ImGuiGradient::internal