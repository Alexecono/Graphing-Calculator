
#ifndef FUNCTION_H
#define FUNCTION_H

#include <glad/glad.h>
#include <vector>
#include <string>
using namespace std;

class Function {
public:
    Function(GLuint newShaderProgram, GLint new_size);
    ~Function();
    void draw() const;
    void set_size(GLint new_size);
    void set_input(string new_input);
    string get_input();
    void update_vertices();
    void update_function();

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint shaderProgram;
    GLint size;
    GLint input_size;
    vector <float> vertices;
    string input;
    double evaluate(double x, string new_input, char last_symbol);

};
#endif //FUNCTION_H