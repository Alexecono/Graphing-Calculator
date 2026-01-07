#include "controls.h"
#include <iostream>

int size = 30;
bool fresh = true;

void change_zoom(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0.0) {
        size += 2;
    }
    if (yoffset < 0.0) {
        size -= 2;
    }

    if (size < 2) {
        size = 2;
    }

    if (size > 15000) {
        size = 15000;
    }

    fresh = false;
}

int get_size() {
    return size;
}

bool is_fresh() {
    return fresh;
}

bool set_fresh() {
    fresh = true;
    return fresh;
}