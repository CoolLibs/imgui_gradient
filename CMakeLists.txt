cmake_minimum_required(VERSION 3.8)

add_library(imgui_gradient)
add_library(imgui_gradient::imgui_gradient ALIAS imgui_gradient)
target_compile_features(imgui_gradient PUBLIC cxx_std_20)

# ---Add source files---
target_include_directories(imgui_gradient PUBLIC include)
file(GLOB SRC_FILES src/*.cpp)
target_sources(imgui_gradient PRIVATE ${SRC_FILES})

# ---Setup warnings---
if (IMGUI_GRADIENT_ENABLE_WARNINGS_AS_ERRORS)
    message("-- [imgui_gradient] Enabling warnings as errors for imgui_gradient")
    if(MSVC)
        target_compile_options(imgui_gradient PRIVATE /WX /W4)
    else()
        target_compile_options(imgui_gradient PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
    endif()
else()
    message("-- [imgui_gradient] Not using warnings as errors for imgui_gradient")
endif()
