#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <imgui_gradient/imgui_gradient.hpp>

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

#include <quick_imgui/quick_imgui.hpp>

int main()
{
    quick_imgui::loop("Test Gradient Widget", []() {
        static ImGuiGradient::GradientWidget gradient;
        gradient.gradient_editor("Gradient", 10.f, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR);
    });
}