

#ifndef CONTROLS_H
#define CONTROLS_H

#include <GLFW/glfw3.h>



void change_zoom(GLFWwindow* window, double xoffset, double yoffset);

int get_size();

bool is_fresh();

bool set_fresh();



#endif //CONTROLS_H