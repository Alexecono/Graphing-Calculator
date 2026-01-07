

#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>

class Shader {
    public:

    Shader();
    ~Shader();
    GLuint getShaderProgram() const;

    private:
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
    GLuint vertexShader, fragmentShader, shaderProgram;
};

#endif //SHADERS_H