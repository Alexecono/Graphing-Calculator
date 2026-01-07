

#ifndef AXIS_H
#define AXIS_H


#include <glad/glad.h>

class Axis {
    public:
    Axis(GLuint newShaderProgram);
    ~Axis();
    void draw() const;

    private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint shaderProgram;

};
#endif //AXIS_H