#pragma once

namespace ImGuiGradient {

/// Severals ways to compute gradient colors between two marks.
enum class Interpolation {
    Linear,   /// Linear gradient between two marks.
    Constant, /// Same color between two marks, it takes the color of right mark.
};

} // namespace ImGuiGradient
