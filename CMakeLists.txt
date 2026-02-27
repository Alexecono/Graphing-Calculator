cmake_minimum_required(VERSION 3.20)
project(GraphingCalculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphingCalculator
        src/main.cpp
        src/glad.c
        src/axis.cpp
        src/shaders.cpp
        src/grid.cpp
        src/controls.cpp
        src/function.cpp
        src/input.cpp
        src/imgui.cpp
        src/imgui_draw.cpp
        src/imgui_impl_glfw.cpp
        src/imgui_impl_opengl3.cpp
        src/imgui_tables.cpp
        src/imgui_widgets.cpp
        include/imconfig.h
        include/imgui.h
        include/imgui_impl_glfw.h
        include/imgui_impl_opengl3.h
)

target_include_directories(GraphingCalculator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG latest
)
FetchContent_MakeAvailable(glfw)



if(WIN32)
    target_link_libraries(GraphingCalculator PRIVATE
            glfw
            opengl32
    )
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(GraphingCalculator PRIVATE
            glfw
            OpenGL::GL
    )
endif()