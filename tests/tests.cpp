#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <imgui_gradient/imgui_gradient.hpp>
#include "../src/Flags.hpp"
#include "../src/Settings.hpp"
#include "../src/utils.hpp"
#include "gradient_options_debug.hpp"

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

#include <quick_imgui/quick_imgui.hpp>

int main(int argc, char* argv[])
{
    doctest::Context context;
    context.run();
    std::string gpu_flag = "";
    if (argc == 2)
    {
        gpu_flag += argv[1];
    }
    if (gpu_flag.compare("-nogpu") != 0)
    {
        quick_imgui::loop("Test Gradient Widget", []() {
            static ImGuiGradient::Flags          flags{};
            static std::default_random_engine    generator{std::random_device{}()};
            static ImGuiGradient::GradientWidget gradient;
            ImGui::Begin("Gradient Editor");
            gradient.widget(
                "Gradient",
                ImGuiGradient::Settings{
                    .horizontal_margin = 10.f,
                    .flags             = flags,
                    .color_flags       = ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR,
                }
            );
            ImGui::End();
            ImGui::Begin("Tests");
            flags = gradient_options_debug();
            ImGui::End();
        });
    }
}

TEST_CASE(
    "Position Mode functions tests"
)
{
    SUBCASE("repeat_position() when position in the range [0,1]")
    {
        float position   = 0.2f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.2f);
    }
    SUBCASE("repeat_position() when position in the range [-1,0]")
    {
        float position   = -0.3f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.7f);
    }
    SUBCASE("repeat_position() when position is negative and < -1")
    {
        float position   = -1.4f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.6f);
    }
    SUBCASE("repeat_position() when position > 1")
    {
        float position   = 1.8f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.8f);
    }
    SUBCASE("repeat_position() when position just before 1")
    {
        float position   = .99f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == .99f);
    }
    SUBCASE("repeat_position() when position just after 1")
    {
        float position   = 1.01f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == .01f);
    }
    SUBCASE("repeat_position() when position just before 0")
    {
        float position   = -0.01f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.99f);
    }
    SUBCASE("repeat_position() when position just after 0")
    {
        float position   = 0.01f;
        float repeat_pos = Utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.01f);
    }

    SUBCASE("mirror_clamp_position() when position in the range [0,1]")
    {
        float position         = 0.7f;
        float mirror_clamp_pos = Utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 0.7f);
    }
    SUBCASE("mirror_clamp_position() when position in the range [-1,0]")
    {
        float position         = -0.4f;
        float mirror_clamp_pos = Utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 0.4f);
    }
    SUBCASE("mirror_clamp_position() when position is negative and < -1")
    {
        float position         = -1.3f;
        float mirror_clamp_pos = Utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 1.f);
    }
    SUBCASE("mirror_clamp_position() when position > 1")
    {
        float position         = 1.8f;
        float mirror_clamp_pos = Utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 1.f);
    }
    SUBCASE("mirror_clamp_position() when position = 1")
    {
        float position         = 1.f;
        float mirror_clamp_pos = Utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 1.f);
    }
    SUBCASE("mirror_clamp_position() when position = 0")
    {
        float position         = 0.f;
        float mirror_clamp_pos = Utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 0.f);
    }

    SUBCASE("mirror_repeat_position() when position in the range [0,1]")
    {
        float position          = 0.4f;
        float mirror_repeat_pos = Utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position in the range [-1,0]")
    {
        float position          = -0.2f;
        float mirror_repeat_pos = Utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.2f);
    }
    SUBCASE("mirror_repeat_position() when position is negative and < -1")
    {
        float position          = -1.6f;
        float mirror_repeat_pos = Utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position > 1")
    {
        float position          = 1.8f;
        float mirror_repeat_pos = Utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.2f);
    }
    SUBCASE("mirror_repeat_position() when position = 1")
    {
        float position          = 1.f;
        float mirror_repeat_pos = Utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 1.f);
    }
    SUBCASE("mirror_repeat_position() when position = 0")
    {
        float position          = 0.f;
        float mirror_repeat_pos = Utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.f);
    }

    SUBCASE("test intermediate functions : modulo(x,mod) when x = 0")
    {
        float x          = 0.f;
        float mod        = 2.f;
        float modulo_res = Utils::modulo(x, mod);

        CHECK(doctest::Approx(modulo_res) == 0.f);
    }
    SUBCASE("test intermediate functions : modulo(x,mod) when x = 1")
    {
        float x          = 1.f;
        float mod        = 2.f;
        float modulo_res = Utils::modulo(x, mod);

        CHECK(doctest::Approx(modulo_res) == 1.f);
    }
}