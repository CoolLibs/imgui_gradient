#include "RelativePosition.hpp"

namespace ImGuiGradient {

auto make_relative_position(float position, WrapMode wrap_mode) -> RelativePosition
{
    return RelativePosition{[&] {
        switch (wrap_mode)
        {
        case WrapMode::Clamp:
        {
            return ImClamp(position, 0.f, 1.f);
        }
        case WrapMode::Repeat:
        {
            return Utils::repeat_position(position);
        }
        case WrapMode::MirrorClamp:
        {
            return Utils::mirror_clamp_position(position);
        }
        case WrapMode::MirrorRepeat:
        {
            return Utils::mirror_repeat_position(position);
        }
        default:
            assert(false && "[RelativePosition::make_relative_position] Invalid enum value");
            return 0.25f;
        }
    }()};
}

} // namespace ImGuiGradient