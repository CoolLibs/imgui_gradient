#pragma once

namespace ImGuiGradient {

/// Controls how a position that is outside of the [0, 1] range is mapped back into that range.
/// This is like the OpenGL texture wrap modes; see https://learnopengl.com/Getting-started/Textures section "Texture Wrapping".
enum class WrapMode {
    /// If it is bigger than 1, maps to 1. If it smaller than 0, maps to 0.
    Clamp,
    /// Maps the number line to a bunch of copies of [0, 1] stuck together.
    /// Basically adds or substracts 1 to the position until it is in the [0, 1] range.
    /// 1.2 maps to 0.2, 1.8 maps to 0.8, -0.2 maps to 0.8, -0.8 maps to 0.2
    Repeat,
    /// `position` mirrored when negative, then clamp it between 0.f and 1.f.
    // TODO(ASG) remove mirror clamp
    MirrorClamp,
    /// Like `Repeat` except that every other range is flipped.
    /// 1.2 maps to 0.8, 1.8 maps to 0.2, -0.2 maps to 0.2, -0.8 maps to 0.8, -1.2 maps to 0.8
    MirrorRepeat,
};

} // namespace ImGuiGradient