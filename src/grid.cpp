#include "grid.h"
#include <vector>

constexpr int max_size = 5000;

Grid :: Grid(GLuint newShaderProgram, GLint new_size) : shaderProgram(newShaderProgram), size(new_size), x_centre(0), y_centre(0) {



    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    update_vertices();
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(GLfloat)), vertices.data(), GL_DYNAMIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Grid :: ~Grid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Grid :: draw() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glUniform3f(glGetUniformLocation(shaderProgram, "colour"),0.6f, 0.6f, 0.6f);
    glDrawArrays(GL_LINES, 0, vertices.size()/3);
    glBindVertexArray(0);
}

void Grid :: set_size(GLint new_size) {
    size = new_size;
}

void Grid :: set_centre(double new_x_centre, double new_y_centre) {
    x_centre = new_x_centre;
    y_centre = new_y_centre;
}

void Grid :: update_vertices() {
    vertices.clear();
    float inv_size = 1.0f / (static_cast<float>(size));
    float y_offset = static_cast<float>(y_centre);
    float x_offset = static_cast<float>(x_centre);

    for (int i = -max_size; i <= max_size; i++) {
        GLfloat y = (static_cast<float>(i) + y_offset) * inv_size;

        vertices.push_back(-1.0f);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        vertices.push_back(1.0f);
        vertices.push_back(y);
        vertices.push_back(0.0f);
    }

    for (int j = -max_size; j <= max_size; j++) {

        GLfloat x = (static_cast<float>(j) + x_offset) * inv_size;

        vertices.push_back(x);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);

        vertices.push_back(x);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);
    }
}

void Grid :: update_grid() {

    update_vertices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(float)), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

