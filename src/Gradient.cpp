#include "Gradient.hpp"

namespace ImGuiGradient {

// Return a ImVec4 according to :
// lower (first mark positionned before position, or nullptr if there is none) and
// upper (First mark positionned after position, or nullptr if there is none)
static auto compute_color_at(const RelativePosition& position, const Mark* lower, const Mark* upper) -> ColorRGBA
{
    if (!lower && !upper)
    {
        return ColorRGBA{0.f, 0.f, 0.f, 1.f};
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
        const float mix_factor = (position.get() - lower->position.get()) /
                                 (upper->position.get() - lower->position.get());
        return ImLerp(lower->color, upper->color, mix_factor);
    }
}

auto Gradient::compute_color_at(RelativePosition position) const -> ColorRGBA
{
    const Mark* lower{nullptr}; // First mark positionned before position, or nullptr if there is none.
    const Mark* upper{nullptr}; // First mark positionned after position, or nullptr if there is none.
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
    return ImGuiGradient::compute_color_at(position, lower, upper);
};

} // namespace ImGuiGradient
