# imgui_gradient

ImGui extension to make a gradient widget.
// TODO(ASG) Small description of the library
// TODO(ASG) Image of the gradient widget (and/or gif!)

## Compatibility

This library is tested and compiles with C++11 on:
- [x] Windows
    - [x] Clang
    - [x] MSVC
- [x] Linux
    - [x] Clang
    - [x] GCC
- [x] MacOS
    - [x] Clang

## Including

To add this library to your project, simply add these three lines to your *CMakeLists.txt* and replace `folder/containing/imgui` with the path to the parent folder containing *imgui*:
```cmake
add_subdirectory(path/to/imgui_gradient)
target_include_directories(imgui_gradient PRIVATE folder/containing/imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui_gradient::imgui_gradient)
```

Then include it as:
```cpp
#include <imgui_gradient/imgui_gradient.hpp>
```

## Using the library

The whole state of the widget is stored in a `ImGuiGradient::GradientWidget` variable. You need to create and store one in order to have access to a gradient. You can then use the `widget()` method to render the ImGui widget:
```cpp
InGuiGradient::GradientWidget gradient_widget{};
gradient_widget.widget("My Gradient");
```

In order to access the gradient data (without the GUI state), you can get the `ImGuiGradient::Gradient` with `gradient_widget.gradient()`.

## Settings

The `widget()` method can also take settings that control its behaviour:
```cpp
InGuiGradient::Settings settings{};

settings.gradient_height = 40.f;

/// Distance under the gradient bar to delete a mark by dragging it down.
/// This behaviour can also be disabled with the Flag::NoDragDowntoDelete.
settings.distance_to_delete_mark_by_dragging_down = 80.f;

settings.horizontal_margin = 10.f;

settings.flags = ImGuiGradient::Flag::None;

settings.color_edit_flags = ImGuiColorEditFlags_None;

/// Controls how the colors are interpolated between two marks.
settings.interpolation_mode = Interpolation::Linear;

/// Controls how the new mark color is chosen.
/// If true, the new mark color will be a random color,
/// otherwise it will be the one that the gradient already has before at the mark position.
settings.should_use_a_random_color_for_the_new_marks = false;

gradient_widget.widget("My Gradient", settings);
```

### ImGuiGradient::Flags

`ImGuiGradient::Flag::None`: All Options are enabled. // TODO(ASG) Make sure this matches the doc in Flags.hpp

`ImGuiGradient::Flag::NoTooltip`: No tooltip when hovering a widget.

`ImGuiGradient::Flag::NoResetButton`: No button to reset to the default value.

`ImGuiGradient::Flag::NoLabel`: No name for gradient widget.

`ImGuiGradient::Flag::NoAddButton`: No "+" button to add a mark.

`ImGuiGradient::Flag::NoRemoveButton`: No "-" button to remove a mark.

`ImGuiGradient::Flag::NoPositionSlider`: No slider widget to chose a precise position when selecting a mark.

`ImGuiGradient::Flag::NoColorEdit`: No color edit widget when selecting a mark.

`ImGuiGradient::Flag::NoDragDownToDelete`: Don't delete a mark by dragging it down.

`ImGuiGradient::Flag::NoBorder`: No border around gradient widget.

`ImGuiGradient::Flag::NoAddAndRemoveButtons`: No "+" and "-" buttons.

`ImGuiGradient::Flag::NoMarkOptions`: No new widgets appear when a mark is selected.


### Interpolation

It controls how the colors are interpolated between two marks.

`ImGuiGradient::Interpolation::Linear`: Linear interpolation.

`ImGuiGradient::Interpolation::Constant`: Constant color between two marks: it uses the color of the mark on the right.

To create a widget that changes the interpolation mode, use:
```cpp
auto ImGuiGradient::gradient_interpolation_mode_selector(
    const char*    label,
    Interpolation& interpolation_mode,
    const bool     should_show_tooltip
) -> bool;
```

## Color randomization

`should_use_a_random_color_for_the_new_marks` allows you to randomize the colors of the marks.
To create a widget for that setting you can use:
```cpp
auto random_mode_checkbox(
    const char* label,
    bool&       should_use_a_random_color_for_the_new_marks,
    const bool  should_show_tooltip
) -> bool;
```

### Random Number Generation

By default we use our own internal `std::default_random_engine`, but you can provide your own that we will use instead:

```cpp
static auto generator = std::default_random_engine{std::random_device{}()};
gradient.widget("My Gradient", generator, settings);
```

*NB:* If all calls to `gradient.widget(...)` provide a random engine, we will not create one on our own.

## Wrap Mode // TODO(ASG) Talk about RelativePosition and how we can sample the gradient, talk about make_relative_position

It controls how the position of a mark that is outside of the [0, 1] range is mapped back into that range. This is like the OpenGL texture wrap modes.

`WrapMode::Clamp` : If it is bigger than 1, maps to 1. If it smaller than 0, maps to 0.

`WrapMode::Repeat` : Maps the number line to a bunch of copies of [0, 1] stuck together. Basically adds or substracts 1 to the position until it is in the [0, 1] range.

`WrapMode::MirrorRepeat` : Like `WrapMode::Repeat` except that every other range is flipped.

To create a widget to change the wrap mode, use:
```cpp
auto ImGuiGradient::wrap_mode_selector(
    const char* label,
    WrapMode&   wrap_mode,
    const bool  should_show_tooltip
) -> bool;
```

For example:
```cpp
ImGuiGradient::Settings settings{};
ImGuiGradient::wrap_mode_selector(
    wrap_mode_widget_name,
    settings.wrap_mode,
    should_show_tooltip);
gradient_widget.widget (widget_name,settings);
```

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
