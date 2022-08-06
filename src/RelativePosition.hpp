#pragma once

#include <cassert>
#include "Utils.hpp"
#include "WrapMode.hpp"

namespace ImGuiGradient {

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

    auto imgui_widget(float width) -> bool
    {
        ImGui::SetNextItemWidth(width);
        static constexpr auto speed{.0001f};
        return ImGui::DragFloat(
            "##3",
            &value,
            speed,
            0.f, 1.f,
            "%.4f",
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

inline auto make_relative_position(float position, WrapMode wrap_mode) -> RelativePosition
{
    const auto relative_pos = RelativePosition{
        [&] {
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
    return relative_pos;
}
} // namespace ImGuiGradient