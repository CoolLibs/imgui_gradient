#include "Gradient.hpp"
#include "utils.hpp"

namespace ImGuiGradient {

auto Gradient::compute_color_at(float position, PositionMode mode) const -> ImVec4
{
    const auto relative_pos = RelativePosition{[&] {
        switch (mode)
        {
        case PositionMode::Clamp:
        {
            return ImClamp(position, 0.f, 1.f);
        }
        case PositionMode::Repeat:
        {
            return utils::repeat_position(position);
        }
        case PositionMode::MirrorClamp:
        {
            return utils::mirror_clamp_position(position);
        }
        case PositionMode::MirrorRepeat:
        {
            return utils::mirror_repeat_position(position);
        }
        default:
            assert(false && "[Gradient::get_color_at] Invalid enum value");
            return 0.5f;
        }
    }()};

    return compute_color_at(relative_pos);
}

auto Gradient::compute_color_at(RelativePosition position) const -> ImVec4
{
    const Mark* lower = nullptr;
    const Mark* upper = nullptr;
    for (const Mark& mark : _marks)
    {
        if (mark.position > position &&
            (!upper || mark.position < upper->position))
        {
            upper = &mark;
        }
        if (mark.position < position &&
            (!lower || mark.position > lower->position))
        {
            lower = &mark;
        }
    }
    if (!lower && !upper)
    {
        return ImVec4{0.f, 0.f, 0.f, 1.f};
    }
    else if (upper && !lower)
    {
        return upper->color;
    }
    else if (!upper && lower)
    {
        return lower->color;
    }

    if (upper == lower)
    {
        return upper->color;
    }
    else
    {
        float mix = (position.get() - lower->get_position()) /
                    (upper->get_position() - lower->get_position());
        return ImLerp(lower->color, upper->color, mix);
    }
};

} // namespace ImGuiGradient
