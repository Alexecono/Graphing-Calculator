cmake_minimum_required(VERSION 3.20)
project(GraphingCalculator)

set(CMAKE_CXX_STANDARD 17)


add_executable(GraphingCalculator
        src/main.cpp
        src/glad.c
        src/axis.h
        src/axis.cpp
        src/shaders.h
        src/shaders.cpp
        src/grid.h
        src/grid.cpp
        src/controls.h
        src/controls.cpp
        src/function.h
        src/function.cpp
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
        src/input.h
        src/input.cpp
)


target_include_directories(GraphingCalculator PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)


find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(GraphingCalculator PRIVATE
        OpenGL::GL
        glfw
)

