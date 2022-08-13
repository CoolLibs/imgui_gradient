# imgui_gradient

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

Create GradientWidget and Settings variables then use `widget()` method
```cpp
InGuiGradient::GradientWidget gradient_widget{};
ImGuiGradient::Settings settings{};
gradient_widget.widget
(
    widget_name,
    settings
);
```

## Settings

There are options you could change to display your gradient.
```cpp
struct Settings {
    float gradient_height = 40.f;
    float distance_to_delete_mark_by_dragging_down = 40.f;
    float horizontal_margin = 10.f;
    ImGuiGradient::Flags flags = ImGuiGradient::Flag::None;
    ImGuiColorEditFlags color_flags = ImGuiColorEditFlags_None;
};
```
`gradient_height` is the gradient bar height.

`distance_to_delete_mark_by_dragging_down` is the distance under the gradient bar where to delete a mark by dragging it down. This behaviour can also be disabled with the `Flag::NoDragDowntoDelete`.

`horizontal_margin` is gradient bar margin.

`flags` are options yous could disable from the gradient widget. 

`color_flags` are ImGui flags to control the behaviour to display colors.


## ImGuiGradient::Flags

`Flag::None` : All Options are enabled.

`Flag::NoTooltip` : No tooltip when hovering a widget.

`Flag::NoResetButton` : No button to reset to the default value.

`Flag::NoLabel` : No name for gradient widget.

`Flag::NoRandomModeCheckBox` : No checkbox to enable or disable the random mode when adding a new color.

`Flag::NoAddButton` : No "+" button to add a mark.

`Flag::NoRemoveButton` : No "-" button to remove a mark.

`Flag::NoPositionSlider` : No slider widget to chose a precise position when selecting a mark.

`Flag::NoColorEdit` : No color edit widget when selecting a mark.

`Flag::NoWrapModeSelector` : No widget to change wrap mode position.

`Flag::NoInterpolationSelector` : No widget to change how gradient colors are computed.

`Flag::NoDragDownToDelete` : Don't delete a mark by dragging it down.

`Flag::NoBorder` : No border around gradient widget.

`Flag::NoAddAndRemoveButtons` : No "+" and "-" buttons.

`Flag::NoMarkOptions` : No new widgets appear when a mark is selected.

`Flag::None` : No selector to change wrap mode position and  how gradient colors are computed.


## GradientWidget class attributes

```cpp
internal::State state{};
WrapMode        wrap_mode{WrapMode::Clamp};
Interpolation   interpolation_mode{Interpolation::Linear};
bool            should_use_a_random_color_for_the_new_marks{false};
```
In `state` there is the gradient and other attributes to make the widget work.
The Gradient is composed of a list of Marks.
A Mark is composed of a color and a RelativePosition between 0.f and 1.f.


## Wrap Mode

It controls how the position of a mark that is outside of the [0, 1] range is mapped back into that range. This is like the OpenGL texture wrap modes.

`WrapMode::Clamp` : If it is bigger than 1, maps to 1. If it smaller than 0, maps to 0.

`WrapMode::Repeat` : Maps the number line to a bunch of copies of [0, 1] stuck together. Basically adds or substracts 1 to the position until it is in the [0, 1] range.

`WrapMode::MirrorRepeat` : Like `WrapMode::Repeat` except that every other range is flipped.

You could disable its selector widget with `Flag::NoWrapModeSelector`.

## Interpolation

It Controls how the colors are interpolated between two marks.
`Interpolation::Linear` : interpolation between two marks.
`Interpolation::Constant` : Constant color between two marks: it uses the color of the mark on the right.

You could disable its selector widget with `Flag::NoInterpolationSelector`.


## Color random generator

`should_use_a_random_color_for_the_new_marks` control the random color mode.
When you add a mark you could add it with a random color.
By default, to do random we use :
```cpp
static auto generator = std::default_random_engine{std::random_device{}()};
```
But it is possible to choose your own `std::default_random_engine` when the widget is created.
```cpp
static auto generator = std::default_random_engine{std::random_device{}()};
gradient.widget(
    widget_name,
    settings,
    generator
);
```
You could disable the random color checkbox widget with `Flag::NoRandomModeCheckBox`.


## Gradient Widget methods

```cpp

auto get_gradient() const -> const Gradient&;
 
void set_mark_position(const Mark& mark, RelativePosition position);
void set_mark_color(const Mark& mark, ColorRGBA color);
void set_wrap_mode(WrapMode new_wrap_mode);
void set_interpolation_mode(Interpolation new_interpolation_mode);
void enable_random_color_mode(bool is_random_enable);

void add_mark(float position);
void add_mark(float position, std::default_random_engine&generator);
void remove_mark(const Mark& mark);

void reset(); // reset state to its default value.

auto widget(
    const char*                 label,
    const Settings&             settings,
    std::default_random_engine& generator
) -> bool;
auto widget(
    const char*     label,
    const Settings& settings
) -> bool;
```

## Compatibility

The current library compile with c++11 on MSVC, Windows Clang, Linux GCC, Linux Clang and MacOS Clang.

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
