

#ifndef CONTROLS_H
#define CONTROLS_H

#include <GLFW/glfw3.h>
#include "imgui.h"



void change_zoom(GLFWwindow* window, double x_offset, double y_offset);

int get_size();

bool is_fresh();

bool set_fresh();

void handle_pan(GLFWwindow* window);

bool is_dragging();

double get_x_centre();

double get_y_centre();



#endif //CONTROLS_H