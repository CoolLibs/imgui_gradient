#pragma once

namespace ImGuiGradient {

/// Controls how the colors are interpolated between two marks.
enum class Interpolation {
    /// Linear interpolation between two marks.
    Linear,
    /// Constant color between two marks: it uses the color of the mark on the right.
    Constant,
};

} // namespace ImGuiGradient
