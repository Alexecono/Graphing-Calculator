#include "shaders.h"

Shader :: Shader() {
    vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    fragmentShaderSource =

        "#version 330 core\n"
        "out vec4 FragColour;\n"
        "uniform vec3 colour;\n"
        "void main()\n"
        "{\n"
        "    FragColour = vec4(colour, 1.0);\n"
        "}\n";

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader :: ~Shader() {
    glDeleteProgram(shaderProgram);
}

GLuint Shader :: getShaderProgram() const {
    return shaderProgram;
}