// https://gist.github.com/galloscript/8a5d179e432e062550972afcd1ecf112

/* TODO(ASG) Replace this with our own documentation

 Usage:

 ::GRADIENT DATA::
 ImGradient gradient;

 ::BUTTON::
 if(ImGui::GradientButton(&gradient))
 {
    //set show editor flag to true/false
 }

 ::EDITOR::
 static ImGradientMark* draggingMark = nullptr;
 static ImGradientMark* selectedMark = nullptr;

 bool updated = ImGui::GradientEditor(&gradient, draggingMark, selectedMark);

 ::GET A COLOR::
 float color[3];
 gradient.getColorAt(0.3f, color); //position from 0 to 1

 ::MODIFY GRADIENT WITH CODE::
 gradient.get().clear();
 gradient.add_mark(0.0f, ImColor(0.2f, 0.1f, 0.0f));
 gradient.add_mark(0.7f, ImColor(120, 200, 255));

 ::WOOD BROWNS PRESET::
 gradient.get().clear();
 gradient.add_mark(0.0f, ImColor(0xA0, 0x79, 0x3D));
 gradient.add_mark(0.2f, ImColor(0xAA, 0x83, 0x47));
 gradient.add_mark(0.3f, ImColor(0xB4, 0x8D, 0x51));
 gradient.add_mark(0.4f, ImColor(0xBE, 0x97, 0x5B));
 gradient.add_mark(0.6f, ImColor(0xC8, 0xA1, 0x65));
 gradient.add_mark(0.7f, ImColor(0xD2, 0xAB, 0x6F));
 gradient.add_mark(0.8f, ImColor(0xDC, 0xB5, 0x79));
 gradient.add_mark(1.0f, ImColor(0xE6, 0xBF, 0x83));

 */

#pragma once

#include <random>
#include "Gradient.hpp"
#include "ImGuiGradientFlags.hpp"
#include "Interpolation.hpp"
#include "gradient_settings.hpp"

namespace ImGuiGradient {
struct State {
    Gradient gradient{};
    Mark*    dragging_mark{};
    Mark*    selected_mark{};
    Mark*    mark_to_hide{};
};

class GradientWidget {
public:
    GradientWidget() = default;
    auto get_gradient() const -> const Gradient& { return state.gradient; }
    auto get_gradient() -> Gradient& { return state.gradient; }
    auto add_mark(const float position, std::default_random_engine& generator) -> bool;

    auto gradient_editor(const char* label, std::default_random_engine& generator, const Settings& settings) -> bool;

private:
    auto draw_gradient_marks(const Mark* mark_to_delete, const ImVec2& gradient_bar_pos, float width, float height) -> bool;
    auto mouse_dragging(const float gradient_bar_bottom, float width, float gradient_bar_pos_x, const Settings& settings) -> bool;

private:
    State         state{};
    WrapMode      position_mode      = WrapMode::Clamp;
    Interpolation interpolation_mode = Interpolation::Linear;
    bool          random_mode        = false;
};

} // namespace ImGuiGradient