#pragma once

#include "ColorRGBA.hpp"
#include "RelativePosition.hpp"

namespace ImGuiGradient {

struct Mark {
    RelativePosition position{0.f};
    ColorRGBA        color{0.f, 0.f, 0.f, 1.f};

    friend auto operator==(const Mark& a, const Mark& b) -> bool
    {
        return a.position == b.position &&
               a.color == b.color;
    };
};

} // namespace ImGuiGradient