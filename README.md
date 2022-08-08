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

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
