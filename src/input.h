

#ifndef INPUT_H
#define INPUT_H

#include <string>
using namespace std;
class Input {

    public:
    Input(GLFWwindow* new_window);
    ~Input();
    void set_input();
    string get_input1();
    string get_input2();

    private:
    char input1[128] = "";
    char input2[128] = "";
    GLFWwindow* window;
};

#endif //INPUT_H