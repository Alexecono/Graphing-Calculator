#include "function.h"
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

Function :: Function(GLuint newShaderProgram, GLint new_size) : shaderProgram(newShaderProgram), size(new_size), input_size(0){



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

    input = "";
}

Function :: ~Function() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Function :: draw() const {

    if (!input.empty()) {
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glUniform3f(glGetUniformLocation(shaderProgram, "colour"),1.0f, 0.0f, 0.0f);
        glDrawArrays(GL_LINE_STRIP, 0, vertices.size()/3);
        glBindVertexArray(0);
    }
}

void Function :: set_size(GLint new_size) {
    size = new_size;
}

void Function :: update_vertices() {
    vertices.clear();

    if (input_size != 0) {
        for (double i = -size; i <= size; i+=0.01*sqrt(size)) {
            float x = static_cast<float>(i)/static_cast<float>(size);
            vertices.push_back(x);
            vertices.push_back(static_cast<float>(evaluate(i, input, ' ') / static_cast<float>(size)));//(evaluate(i, input, ' '))) / (static_cast<float>(size)));
            vertices.push_back(0.0f);
        }
    }
}

void Function :: update_function() {

    update_vertices();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(float)), vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Function::set_input(string new_input) {
    input.clear();
    for (int i = 0; i < new_input.size(); i++) {
        if (new_input[i] != ' ') {
            input += new_input[i];
        }
    }
    input_size = input.size();
}

string Function :: get_input() {
    return input;
}


double Function :: evaluate(double x, string new_input, char last_symbol) {
    double y = 0.0;
    int digits = 1;

    for (int i = 0; i < new_input.size(); i++) {
        if (new_input[i] >= '0' && new_input[i] <= '9') {
            y *= digits;
            y += new_input[i] - '0';
            digits = 10;
        } else {
            digits = 1;
        }
        if (new_input[i] == 'x') {
            y += x;
        }
        if (((new_input[i] >= '0' && new_input[i] <= '9')|| (new_input[i] == 'x'))
            &&(last_symbol == '-' && i + 1 < new_input.size()
                && (new_input[i + 1] < 0 || new_input[i + 1] > 9)) || (i == new_input.size() - 1 && last_symbol == '-')) {
            y *= -1;
                }
        else if (new_input[i] == '+') {
            string re_input = new_input.substr(i + 1);
            y += evaluate(x, re_input, '+');
            break;
        } else if (new_input[i] == '-') {
            string re_input = new_input.substr(i + 1);
            y += evaluate(x, re_input, '-');
            break;
        } else if (new_input[i] == '*') {
            string re_input = new_input.substr(i + 1);
            y *= evaluate(x, re_input, '*');
            break;
        } else if (new_input[i] == '/') {
            string re_input = new_input.substr(i + 1);
            y /= evaluate(x, re_input, '/');
            break;
        }
    }


    return y;
}

