cmake_minimum_required(VERSION 3.11)
project(imgui_gradient-tests)

add_executable(${PROJECT_NAME} tests.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

set(IMGUI_GRADIENT_ENABLE_WARNINGS_AS_ERRORS ON)
add_subdirectory(.. ${CMAKE_CURRENT_SOURCE_DIR}/build/imgui_gradient)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui_gradient::imgui_gradient)

# ---Add doctest---
include(FetchContent)
FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest
    GIT_TAG b7c21ec5ceeadb4951b00396fc1e4642dd347e5f
)
FetchContent_MakeAvailable(doctest)
target_link_libraries(${PROJECT_NAME} PRIVATE doctest::doctest)

# ---Ignore .vscode/settings.json in Git---
find_package(Git QUIET)
if(GIT_FOUND)
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
    if (EXISTS "${PARENT_DIR}/.git")
        execute_process(COMMAND ${GIT_EXECUTABLE} update-index --assume-unchanged .vscode/settings.json
            WORKING_DIRECTORY ${PARENT_DIR}
            RESULT_VARIABLE ERRORS)
        if(NOT ERRORS EQUAL "0")
            message("Git assume-unchanged failed: ${ERRORS}")
        endif()
    else()
        message("No Git repository found.")
    endif()
else()
    message("Git executable not found.")
endif()

# ---Add quick_imgui---
include(FetchContent)
FetchContent_Declare(
    quick_imgui
    GIT_REPOSITORY https://github.com/CoolLibs/quick_imgui
    GIT_TAG b02caa355c7ba18d21aa2a6205602a93fe44db08
)
FetchContent_MakeAvailable(quick_imgui)
target_include_directories(imgui_gradient PRIVATE ${quick_imgui_SOURCE_DIR}/lib) # TODO(ASG) Put this in the readme of quick_imgui, and in the readme of this lib
target_link_libraries(${PROJECT_NAME} PRIVATE quick_imgui::quick_imgui)
