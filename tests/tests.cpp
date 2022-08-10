#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <imgui_gradient/imgui_gradient.hpp>
#include <quick_imgui/quick_imgui.hpp>
#include "../src/Utils.hpp" // to test wrap mode fonctions
#include "checkboxes_for_all_flags.hpp"

auto main(int argc, char* argv[]) -> int
{
    const int  exit_code              = doctest::Context{}.run(); // Run all unit tests
    const bool should_run_imgui_tests = argc < 2 || strcmp(argv[1], "-nogpu") != 0;
    if (
        should_run_imgui_tests &&
        exit_code == 0 // Only open the window if the tests passed; this makes it easier to notice when some tests fail
    )
    {
        auto generator = std::default_random_engine{std::random_device{}()}; // TODO(ASG) This isn't used anywhere. Put a checkbox in the Options window to decide if we use our custom generator or imgui_gradient's default one.
        auto gradient  = ImGuiGradient::GradientWidget{};
        quick_imgui::loop("imgui_gradient tests", [&]() {
            ImGui::Begin("Flags");
            const auto flags = checkboxes_for_all_flags();
            ImGui::End();
            ImGui::Begin("Programmatic Actions");
            // TODO(ASG) test the programmatic setters (mark position, mark color, adding or removing marks, changing the wrap mode / interpolation mode, etc.)
            ImGui::End();
            ImGui::Begin("imgui_gradient tests");
            ImGuiGradient::Settings settings{};
            settings.horizontal_margin = 10.f,
            settings.flags             = flags,
            settings.color_flags       = ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR,
            gradient.widget(
                "Gradient",
                settings
            );
            ImGui::End();
        });
    }
    return exit_code;
}

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

TEST_CASE("Wrap modes")
{
    SUBCASE("repeat_position() when position in the range [0,1]")
    {
        const float position   = 0.2f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.2f);
    }
    SUBCASE("repeat_position() when position in the range [-1,0]")
    {
        const float position   = -0.3f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.7f);
    }
    SUBCASE("repeat_position() when position is < -1")
    {
        const float position   = -1.4f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.6f);
    }
    SUBCASE("repeat_position() when position > 1")
    {
        const float position   = 1.8f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.8f);
    }
    SUBCASE("repeat_position() when position just before 1")
    {
        const float position   = .99f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == .99f);
    }
    SUBCASE("repeat_position() when position just after 1")
    {
        const float position   = 1.01f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == .01f);
    }
    SUBCASE("repeat_position() when position just before 0")
    {
        const float position   = -0.01f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.99f);
    }
    SUBCASE("repeat_position() when position just after 0")
    {
        const float position   = 0.01f;
        const float repeat_pos = internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.01f);
    }

    SUBCASE("mirror_repeat_position() when position in the range [0,1]")
    {
        const float position          = 0.4f;
        const float mirror_repeat_pos = internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position in the range [-1,0]")
    {
        const float position          = -0.2f;
        const float mirror_repeat_pos = internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.2f);
    }
    SUBCASE("mirror_repeat_position() when position is negative and < -1")
    {
        const float position          = -1.6f;
        const float mirror_repeat_pos = internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position > 1")
    {
        const float position          = 1.8f;
        const float mirror_repeat_pos = internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.2f);
    }
    SUBCASE("mirror_repeat_position() when position = 1")
    {
        const float position          = 1.f;
        const float mirror_repeat_pos = internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 1.f);
    }
    SUBCASE("mirror_repeat_position() when position = 0")
    {
        const float position          = 0.f;
        const float mirror_repeat_pos = internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.f);
    }

    SUBCASE("test intermediate functions : modulo(x,mod) when x = 0")
    {
        const float x          = 0.f;
        const float mod        = 2.f;
        const float modulo_res = internal::modulo(x, mod);

        CHECK(doctest::Approx(modulo_res) == 0.f);
    }
    SUBCASE("test intermediate functions : modulo(x, mod) when x = 1")
    {
        const float x          = 1.f;
        const float mod        = 2.f;
        const float modulo_res = internal::modulo(x, mod);

        CHECK(doctest::Approx(modulo_res) == 1.f);
    }
}