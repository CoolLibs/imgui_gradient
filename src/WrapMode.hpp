#pragma once

namespace ImGuiGradient {

/// Severals ways to make a `position` relative (between 0.f and 1.f).
enum class WrapMode {
    Clamp,       /// `position` clamped between 0.f and 1.f.
    Repeat,      /// Integer part of `position` ignored to get a relative position.
    MirrorClamp, /// `position` mirrored when odd, then clamp it between 0.f and 1.f.
    MirrorRepeat /// `position` mirrored when odd, then integer part ignored to to get a relative position.
};

} // namespace ImGuiGradient