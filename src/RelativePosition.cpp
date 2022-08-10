#include "RelativePosition.hpp"
#include "Utils.hpp"

namespace ImGuiGradient {

auto make_relative_position(float position, WrapMode wrap_mode) -> RelativePosition
{
    return RelativePosition{[&] {
        switch (wrap_mode)
        {
        case WrapMode::Clamp:
        {
            return Utils::clamp(position);
        }
        case WrapMode::Repeat:
        {
            return Utils::repeat_position(position);
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