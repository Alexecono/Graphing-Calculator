
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
    Axis axis (shader.getShaderProgram());
    Grid grid(shader.getShaderProgram(), 30);
    Function function(shader.getShaderProgram(), 30);
    Input input(window);

    glfwSetScrollCallback(window, change_zoom);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!is_fresh()) {
            grid.set_size(get_size());
            grid.update_grid();
            function.set_size(get_size());
            set_fresh();
        }

        grid.draw();
        axis.draw();
        function.update_function();
        function.draw();

        input.set_input();
        function.set_input(input.get_input());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
