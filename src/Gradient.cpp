#include "Gradient.hpp"

namespace ImGuiGradient {

auto Gradient::compute_color_at(RelativePosition position) const -> ImVec4 // TODO(ASG) return type should be ColorRGBA
{
    const Mark* lower{nullptr}; // TODO(ASG) explain what this is
    const Mark* upper{nullptr}; // e.g. upper is the first mark positionned after position, or nullptr if there is none.
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
    // TODO(ASG) Move the whole block above into a function, and give it a proper name and documentation

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
        float mix = (position.get() - lower->position.get()) / // TODO(ASG) const, and rename as mix_factor
                    (upper->position.get() - lower->position.get());
        return ImLerp(lower->color, upper->color, mix);
    }
};

} // namespace ImGuiGradient
