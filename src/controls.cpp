#include "controls.h"
#include <iostream>

int size = 30;
double last_x = 0.0;
double last_y = 0.0;
double x_centre = 0.0;
double y_centre = 0.0;
bool dragging = false;
bool fresh = true;

void change_zoom(GLFWwindow* window, double x_offset, double y_offset) {
    if (y_offset > 0.0) {
        size += 2;
    }
    if (y_offset < 0.0) {
        size -= 2;
    }

    if (size < 2) {
        size = 2;
    }

    if (size > 5000) {
        size = 5000;
    }

    fresh = false;
}

int get_size() {
    return size;
}

bool is_fresh() {
    return fresh;
}

void handle_pan(GLFWwindow* window) {

    if (ImGui::GetIO().WantCaptureMouse)
        return;

    double x, y;
    glfwGetCursorPos(window, &x, &y);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

        if (!dragging) {
            dragging = true;
            last_x = x;
            last_y = y;
        } else {
            double dx = x - last_x;
            double dy = y - last_y;


            x_centre += dx * 0.01;
            y_centre -= dy * 0.01;

            last_x = x;
            last_y = y;
        }
    } else {
        dragging = false;
    }
}


bool set_fresh() {
    fresh = true;
    return fresh;
}

double get_x_centre() {
    return x_centre;
}

double get_y_centre() {
    return y_centre;
}
