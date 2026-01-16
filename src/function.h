
#ifndef FUNCTION_H
#define FUNCTION_H

#include <glad/glad.h>
#include <vector>
#include <string>
using namespace std;

enum class Type {
    Number, Operator
};

struct CustomInput {
    Type type;
    double number;
    char operation;
};

class Function {
public:
    Function(GLuint newShaderProgram, GLint new_size);
    ~Function();
    void draw() const;
    void set_size(GLint new_size);
    void set_input(string new_input);
    void set_centre(double new_x_centre, double new_y_centre);
    string get_input();
    void update_vertices();
    void update_function();


private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint shaderProgram;
    GLint size;
    GLint input_size;
    double x_centre;
    double y_centre;
    vector <float> vertices;
    string input;

    vector<CustomInput> get_custom_vector(double x, string new_input);
    double evaluate(double x, string new_input, vector<CustomInput> brackets_vector = {}, bool brackets = false);
    double calculate(double num1, double num2, char operation);

};
#endif //FUNCTION_H