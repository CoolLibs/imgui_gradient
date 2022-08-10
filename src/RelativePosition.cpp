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
            return internal::clamp(position);
        }
        case WrapMode::Repeat:
        {
            return internal::repeat_position(position);
        }
        case WrapMode::MirrorRepeat:
        {
            return internal::mirror_repeat_position(position);
        }
        default:
            assert(false && "[RelativePosition::make_relative_position] Invalid enum value");
            return 0.25f;
        }
    }()};
}

auto RelativePosition::imgui_widget(float width) -> bool
{
    ImGui::SetNextItemWidth(width);
    return ImGui::DragFloat(
        "##3", // TODO(ASG) Receive this as a parameter (with a default value). If we want to render two RelativePosition in the same window this will be a problem if they have the same label.
        &value,
        .0001f,   /* speed */
        0.f, 1.f, /* min and max */
        "%.4f",
        ImGuiSliderFlags_AlwaysClamp
    );
}

} // namespace ImGuiGradient