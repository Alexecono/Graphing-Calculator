#include "grid.h"
#include <vector>
using namespace std;

Grid :: Grid(GLuint newShaderProgram, GLint new_size) : shaderProgram(newShaderProgram), size(new_size){



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

void Grid :: update_vertices() {
    vertices.clear();

    for (int i = 0; i <= size; i++) {
        GLfloat y = (static_cast<float>(i) / static_cast<float>(size));

        vertices.push_back(-1.0f);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        vertices.push_back(1.0f);
        vertices.push_back(y);
        vertices.push_back(0.0f);

        vertices.push_back(-1.0f);
        vertices.push_back(-y);
        vertices.push_back(0.0f);

        vertices.push_back(1.0f);
        vertices.push_back(-y);
        vertices.push_back(0.0f);
    }

    for (int j = 0; j <= size; j++) {

        GLfloat x = (static_cast<float>(j) / static_cast<float>(size));

        vertices.push_back(x);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);

        vertices.push_back(x);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);

        vertices.push_back(-x);
        vertices.push_back(-1.0f);
        vertices.push_back(0.0f);

        vertices.push_back(-x);
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

