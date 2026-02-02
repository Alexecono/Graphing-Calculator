#include "controls.h"
#include <cmath>


constexpr int min_size = 2;
constexpr int max_size = 5000;
constexpr int min_speed = 2;
constexpr float zoom_speed_factor = 0.01;
constexpr float pan_factor = 0.001;
int size = 30;
double last_x = 0.0;
double last_y = 0.0;
double x_centre = 0.0;
double y_centre = 0.0;
bool dragging = false;
bool fresh = true;

void change_zoom(GLFWwindow* window, double x_offset, double y_offset) {
    if (y_offset > 0.0) {
        size += std::max(min_speed, static_cast<int>(std::round(zoom_speed_factor * size)));
    }
    if (y_offset < 0.0) {
        size -= std::max(min_speed, static_cast<int>(std::round(zoom_speed_factor * size)));
    }

    if (size < min_size) {
        size = min_size;
    }

    if (size > max_size) {
        size = max_size;
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


            x_centre += dx * pan_factor * size;
            y_centre -= dy * pan_factor * size;

            last_x = x;
            last_y = y;
        }
    } else {
        dragging = false;
    }
}


void set_fresh() {
    fresh = true;
}

double get_x_centre() {
    return x_centre;
}

double get_y_centre() {
    return y_centre;
}
