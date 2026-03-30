
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "axis.h"
#include "grid.h"
#include "shaders.h"
#include "controls.h"
#include "function.h"
#include "input.h"
using namespace std;


int main() {
    constexpr int default_grid_size = 30;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(1500, 1500, "Graphing Calculator", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 1500, 1500);
    glClearColor(0.75f, 0.75f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);


    Shader shader;
    Axis axis (shader.getShaderProgram(), default_grid_size);
    Grid grid(shader.getShaderProgram(), default_grid_size);
    Function function1(shader.getShaderProgram(), default_grid_size, 1.0f, 0.0f, 0.0f);
    Function function2(shader.getShaderProgram(), default_grid_size, 0.0f, 0.0f, 1.0f);
    Input input(window);

    glfwSetScrollCallback(window, change_zoom);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!is_fresh()) {
            grid.set_size(get_size());
            function1.set_size(get_size());
            function2.set_size(get_size());
            axis.set_size(get_size());
            set_fresh();
        }

        double x_centre = get_x_centre();
        double y_centre = get_y_centre();

        handle_pan(window);
        function1.set_centre(x_centre, y_centre);
        function2.set_centre(x_centre, y_centre);
        grid.set_centre(x_centre, y_centre);
        axis.set_centre(x_centre, y_centre);

        grid.update_grid();
        function1.update_function();
        function2.update_function();
        axis.update_axis();

        grid.draw();
        axis.draw();
        function1.draw();
        function2.draw();

        input.set_input();
        function1.set_input(input.get_input1());
        function2.set_input(input.get_input2());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
