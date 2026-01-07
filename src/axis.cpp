#include "axis.h"

Axis :: Axis(GLuint newShaderProgram) : shaderProgram(newShaderProgram){
    GLfloat vertices[] = {

        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, -1.0f,  0.0f,
        0.0f, 1.0f,  0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Axis :: ~Axis() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Axis :: draw() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glLineWidth(3.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "colour"),0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);
}