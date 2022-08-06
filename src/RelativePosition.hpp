#pragma once

#include <cassert>

namespace ImGuiGradient {

// TODO(ASG) Move the switch here
auto make_relative_position(float position, WrapMode wrap_mode) -> RelativePosition
{
}

/// Represents a number between 0 and 1.
class RelativePosition {
public:
    /// `position` has to be betweend 0 and 1.
    explicit RelativePosition(float position)
        : value(position)
    {
        assert_invariants();
    }

    /// Returns a number between 0 and 1.
    auto get() const -> float { return value; }

    /// `position` has to be betweend 0 and 1.
    void set(float position)
    {
        value = position;
        assert_invariants();
    }

    auto widget(float width) -> bool // TODO(ASG) rename as imgui_widget()
    {
        ImGui::SetNextItemWidth(width);
        static constexpr auto speed{1.f}; // TODO(ASG) Find a nice value
        return ImGui::DragFloat(
            "##3",
            &value,
            speed,
            0.f, 1.f,
            "%.3f", // TODO(ASG) increase precision to 4 or 5
            ImGuiSliderFlags_AlwaysClamp
        );
    }

    friend auto operator<(const RelativePosition& a, const RelativePosition& b) -> bool { return a.get() < b.get(); }
    friend auto operator>(const RelativePosition& a, const RelativePosition& b) -> bool { return a.get() > b.get(); }
    friend auto operator==(const RelativePosition& a, const RelativePosition& b) -> bool { return a.get() == b.get(); }
    friend auto operator!=(const RelativePosition& a, const RelativePosition& b) -> bool { return !(a == b); }

private:
    void assert_invariants() const
    {
        assert(0.f <= value && value <= 1.f && "RelativePosition value should be between 0.f and 1.f");
    }

private:
    float value{0.f};
};

} // namespace ImGuiGradient