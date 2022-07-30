#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <imgui_gradient/utils.h>
#include <imgui_gradient/imgui_gradient.hpp>

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

#include <quick_imgui/quick_imgui.hpp>

TEST_CASE(
    "Position Mode functions tests"
)
{
    SUBCASE("repeat_position() when position in the range [0,1]")
    {
        float position   = 0.2f;
        float repeat_pos = utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.2f);
    }
    SUBCASE("repeat_position() when position in the range [-1,0]")
    {
        float position   = -0.3f;
        float repeat_pos = utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.7f);
    }
    SUBCASE("repeat_position() when position is negative and < -1")
    {
        float position   = -1.4f;
        float repeat_pos = utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.6f);
    }
    SUBCASE("repeat_position() when position > 1")
    {
        float position   = 1.8f;
        float repeat_pos = utils::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos) == 0.8f);
    }

    SUBCASE("mirror_clamp_position() when position in the range [0,1]")
    {
        float position         = 0.7f;
        float mirror_clamp_pos = utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 0.7f);
    }
    SUBCASE("mirror_clamp_position() when position in the range [-1,0]")
    {
        float position         = -0.4f;
        float mirror_clamp_pos = utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 0.4f);
    }
    SUBCASE("mirror_clamp_position() when position is negative and < -1")
    {
        float position         = -1.3f;
        float mirror_clamp_pos = utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 1.f);
    }
    SUBCASE("mirror_clamp_position() when position > 1")
    {
        float position         = 1.8f;
        float mirror_clamp_pos = utils::mirror_clamp_position(position);

        CHECK(doctest::Approx(mirror_clamp_pos) == 1.f);
    }

    SUBCASE("mirror_repeat_position() when position in the range [0,1]")
    {
        float position          = 0.4f;
        float mirror_repeat_pos = utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position in the range [-1,0]")
    {
        float position          = -0.2f;
        float mirror_repeat_pos = utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.2f);
    }
    SUBCASE("mirror_repeat_position() when position is negative and < -1")
    {
        float position          = -1.6f;
        float mirror_repeat_pos = utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position > 1")
    {
        float position          = 1.8f;
        float mirror_repeat_pos = utils::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos) == 0.2f);
    }
}

int main()
{
    doctest::Context context;

    context.run();
    quick_imgui::loop("Test Gradient Widget", []() {
        static ImGuiGradient::GradientWidget gradient;
        gradient.gradient_editor("Gradient", 10.f, ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR);
    });
}