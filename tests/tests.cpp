#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <imgui_gradient/imgui_gradient.hpp>
#include <quick_imgui/quick_imgui.hpp>
#include "../generated/checkboxes_for_all_flags.inl"
#include "../src/Utils.hpp" // to test wrap mode functions
#include "../src/button_disabled.hpp"

auto main(int argc, char* argv[]) -> int
{
    const int  exit_code              = doctest::Context{}.run(); // Run all unit tests
    const bool should_run_imgui_tests = argc < 2 || strcmp(argv[1], "-nogpu") != 0;
    if (
        should_run_imgui_tests &&
        exit_code == 0 // Only open the window if the tests passed; this makes it easier to notice when some tests fail
    )
    {
        auto gradient  = ImGuiGradient::GradientWidget{};
        auto gradient2 = ImGuiGradient::GradientWidget{};
        quick_imgui::loop("imgui_gradient tests", [&]() {
            ImGui::Begin("Framerate");
            ImGui::Text("%.3f FPS", ImGui::GetIO().Framerate);
            ImGui::End();
            ImGui::Begin("Flags");
            const auto flags = checkboxes_for_all_flags();
            ImGui::End();
            ImGui::Begin("Options");
            static auto custom_generator = false;
            ImGui::Checkbox("Use our custom generator", &custom_generator);
            ImGui::End();
            ImGui::Begin("Programmatic Actions");
            if (gradient.gradient().is_empty())
            {
                ImGuiGradient::button_disabled("Remove a mark", "gradient is empty");
            }
            else
            {
                if (ImGui::Button("Remove a mark"))
                {
                    gradient.gradient().remove_mark(ImGuiGradient::MarkId{gradient.gradient().get_marks().front()});
                }
            }
            if (ImGui::Button("Add a mark"))
            {
                gradient.gradient().add_mark(ImGuiGradient::Mark{ImGuiGradient::RelativePosition{0.5f}, ImVec4{0.f, 0.f, 0.f, 1.f}});
            };
            static auto position{0.f};
            if (ImGui::Button("Set mark position") && !gradient.gradient().is_empty())
            {
                gradient.gradient().set_mark_position(
                    ImGuiGradient::MarkId{gradient.gradient().get_marks().front()},
                    ImGuiGradient::RelativePosition{position}
                );
            };
            ImGui::SameLine();
            ImGui::DragFloat("position to add a mark", &position, .0001f, /* speed */
                             0.f, 1.f,                                    /* min and max */
                             "%.4f" /* precision */);
            static auto color = ImVec4{0.f, 0.f, 0.f, 1.f};
            if (ImGui::Button("Set mark color") && !gradient.gradient().is_empty())
            {
                gradient.gradient().set_mark_color(ImGuiGradient::MarkId{gradient.gradient().get_marks().front()}, color);
            };
            ImGui::SameLine();
            ImGui::ColorEdit4(
                "##colorpicker1",
                reinterpret_cast<float*>(&color),
                ImGuiColorEditFlags_NoTooltip |
                    ImGuiColorEditFlags_NoInputs
            );
            static ImGuiGradient::Settings settings{};
            static ImGuiGradient::WrapMode wrap_mode{};
            ImGuiGradient::wrap_mode_selector("Position Mode", wrap_mode);
            ImGuiGradient::gradient_interpolation_mode_selector("Interpolation Mode", settings.interpolation_mode);
            ImGuiGradient::random_mode_checkbox("Randomize new marks' color", settings.should_use_a_random_color_for_the_new_marks);

            ImGui::End();
            ImGui::Begin("imgui_gradient tests");
            settings.flags            = flags;
            settings.color_edit_flags = ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR;
            if (custom_generator)
            {
                static auto generator = std::default_random_engine{std::random_device{}()};
                gradient.widget(
                    "Gradient",
                    generator,
                    settings
                );
                gradient2.widget(
                    "Gradient2",
                    generator,
                    settings
                );
            }
            else
            {
                gradient.widget(
                    "Gradient",
                    settings
                );
                gradient2.widget(
                    "Gradient2",
                    settings
                );
            }
            ImGui::End();
        });
    }
    return exit_code;
}

// Check out doctest's documentation: https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

TEST_CASE("Interpolation modes")
{
    // Gradient from black to white
    ImGuiGradient::Gradient gradient{{
        ImGuiGradient::Mark{ImGuiGradient::RelativePosition{0.f}, ImGuiGradient::ColorRGBA{0.f, 0.f, 0.f, 1.f}},
        ImGuiGradient::Mark{ImGuiGradient::RelativePosition{1.f}, ImGuiGradient::ColorRGBA{1.f, 1.f, 1.f, 1.f}},
    }};

    CHECK(doctest::Approx(gradient.at(ImGuiGradient::RelativePosition{0.25f}, ImGuiGradient::Interpolation::Linear).x) == 0.25f);
    CHECK(doctest::Approx(gradient.at(ImGuiGradient::RelativePosition{0.75f}, ImGuiGradient::Interpolation::Linear).x) == 0.75f);
    CHECK(doctest::Approx(gradient.at(ImGuiGradient::RelativePosition{0.25f}, ImGuiGradient::Interpolation::Constant).x) == 1.f);
    CHECK(doctest::Approx(gradient.at(ImGuiGradient::RelativePosition{0.75f}, ImGuiGradient::Interpolation::Constant).x) == 1.f);
}

TEST_CASE("Wrap modes")
{
    SUBCASE("clamp_position() when position in the range [0,1]")
    {
        const float position   = 0.3f;
        const auto  repeat_pos = ImGuiGradient::internal::clamp_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == 0.3f);
    }
    SUBCASE("clamp_position() when position in the range [-1,0]")
    {
        const float position  = -0.4f;
        const auto  clamp_pos = ImGuiGradient::internal::clamp_position(position);

        CHECK(doctest::Approx(clamp_pos.get()) == 0.f);
    }
    SUBCASE("clamp_position() when position is < -1")
    {
        const float position  = -1.4f;
        const auto  clamp_pos = ImGuiGradient::internal::clamp_position(position);

        CHECK(doctest::Approx(clamp_pos.get()) == 0.f);
    }
    SUBCASE("clamp_position() when position > 1")
    {
        const float position  = 1.9f;
        const auto  clamp_pos = ImGuiGradient::internal::clamp_position(position);

        CHECK(doctest::Approx(clamp_pos.get()) == 1.f);
    }
    SUBCASE("clamp_position() when position = 1")
    {
        const float position  = 1.f;
        const auto  clamp_pos = ImGuiGradient::internal::clamp_position(position);

        CHECK(doctest::Approx(clamp_pos.get()) == 1.f);
    }
    SUBCASE("clamp_position() when position = 0")
    {
        const float position  = 0.f;
        const auto  clamp_pos = ImGuiGradient::internal::clamp_position(position);

        CHECK(doctest::Approx(clamp_pos.get()) == 0.f);
    }

    SUBCASE("repeat_position() when position in the range [0,1]")
    {
        const float position   = 0.2f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == 0.2f);
    }
    SUBCASE("repeat_position() when position in the range [-1,0]")
    {
        const float position   = -0.3f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == 0.7f);
    }
    SUBCASE("repeat_position() when position is < -1")
    {
        const float position   = -1.4f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == 0.6f);
    }
    SUBCASE("repeat_position() when position > 1")
    {
        const float position   = 1.8f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == 0.8f);
    }
    SUBCASE("repeat_position() when position just before 1")
    {
        const float position   = .99f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == .99f);
    }
    SUBCASE("repeat_position() when position just after 1")
    {
        const float position   = 1.01f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == .01f);
    }
    SUBCASE("repeat_position() when position just before 0")
    {
        const float position   = -0.01f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == 0.99f);
    }
    SUBCASE("repeat_position() when position just after 0")
    {
        const float position   = 0.01f;
        const auto  repeat_pos = ImGuiGradient::internal::repeat_position(position);

        CHECK(doctest::Approx(repeat_pos.get()) == 0.01f);
    }

    SUBCASE("mirror_repeat_position() when position in the range [0,1]")
    {
        const float position          = 0.4f;
        const auto  mirror_repeat_pos = ImGuiGradient::internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos.get()) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position in the range [-1,0]")
    {
        const float position          = -0.2f;
        const auto  mirror_repeat_pos = ImGuiGradient::internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos.get()) == 0.2f);
    }
    SUBCASE("mirror_repeat_position() when position is negative and < -1")
    {
        const float position          = -1.6f;
        const auto  mirror_repeat_pos = ImGuiGradient::internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos.get()) == 0.4f);
    }
    SUBCASE("mirror_repeat_position() when position > 1")
    {
        const float position          = 1.8f;
        const auto  mirror_repeat_pos = ImGuiGradient::internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos.get()) == 0.2f);
    }
    SUBCASE("mirror_repeat_position() when position = 1")
    {
        const float position          = 1.f;
        const auto  mirror_repeat_pos = ImGuiGradient::internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos.get()) == 1.f);
    }
    SUBCASE("mirror_repeat_position() when position = 0")
    {
        const float position          = 0.f;
        const auto  mirror_repeat_pos = ImGuiGradient::internal::mirror_repeat_position(position);

        CHECK(doctest::Approx(mirror_repeat_pos.get()) == 0.f);
    }

    SUBCASE("test intermediate functions : modulo(x,mod) when x = 0")
    {
        const float x          = 0.f;
        const float mod        = 2.f;
        const float modulo_res = ImGuiGradient::internal::modulo(x, mod);

        CHECK(doctest::Approx(modulo_res) == 0.f);
    }
    SUBCASE("test intermediate functions : modulo(x, mod) when x = 1")
    {
        const float x          = 1.f;
        const float mod        = 2.f;
        const float modulo_res = ImGuiGradient::internal::modulo(x, mod);

        CHECK(doctest::Approx(modulo_res) == 1.f);
    }
}