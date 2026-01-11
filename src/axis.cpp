#include "axis.h"

Axis :: Axis(GLuint newShaderProgram, GLuint new_size) : shaderProgram(newShaderProgram), size (new_size), x_centre(0), y_centre(0) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(GLfloat), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Axis :: ~Axis() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Axis :: set_centre(double new_x_centre, double new_y_centre) {
    x_centre = new_x_centre;
    y_centre = new_y_centre;
}

void Axis :: set_size(GLint new_size) {
    size = new_size;
}

void Axis :: draw() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glLineWidth(3.0f);
    glUniform3f(glGetUniformLocation(shaderProgram, "colour"),0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_LINES, 0, 4);
    glBindVertexArray(0);
}

void Axis :: update_vertices() {
    vertices.clear();

    float x_offset = static_cast<float>(x_centre);
    float y_offset = static_cast<float>(y_centre);
    float inv_size = 1.0f / static_cast<float>(size);
    vertices.assign({
        -1.0f, y_offset * inv_size, 0.0f,
        1.0f, y_offset * inv_size, 0.0f,
        x_offset * inv_size, -1.0f,  0.0f,
        x_offset * inv_size, 1.0f,  0.0f
    });


}

void Axis :: update_axis() {
    update_vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(float)), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}