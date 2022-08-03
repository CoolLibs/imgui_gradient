#pragma once

#include <assert.h>

class RelativePosition {
public:
    RelativePosition(float position)
        : value(position)
    {
        IM_ASSERT(0.f <= position && position <= 1.f);
    }

    auto get() const -> float { return value; }
    auto get() -> float& { return value; }
    void set(const float pos) { value = pos; }

    friend auto operator<(const RelativePosition& a, const RelativePosition& b) -> bool { return a.get() < b.get(); }
    friend auto operator>(const RelativePosition& a, const RelativePosition& b) -> bool { return a.get() > b.get(); }
    friend auto operator==(const RelativePosition& a, const RelativePosition& b) -> bool { return a.get() == b.get(); }
    friend auto operator!=(const RelativePosition& a, const RelativePosition& b) -> bool { return !(a == b); }

private:
    float value{};
};