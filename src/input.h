

#ifndef INPUT_H
#define INPUT_H

#include <string>
using namespace std;
class Input {

    public:
    Input(GLFWwindow* new_window);
    ~Input();
    void set_input();
    string get_input();

    private:
    char input[128] = "";
    GLFWwindow* window;
};

#endif //INPUT_H