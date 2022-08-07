#pragma once

#include "Mark.hpp"

namespace ImGuiGradient {

namespace internal {

struct SurroundingMarks {
    /// First mark positionned before `position`, or nullptr if there is none // TODO(ASG) This comment is wrong because I have no idea what "position" is. The comments would make more sense if they were around get_marks_surrounding()
    const Mark* lower{nullptr};
    /// First mark positionned after `position`, or nullptr if there is none // TODO(ASG) same
    const Mark* upper{nullptr};
};

}} // namespace ImGuiGradient::internal