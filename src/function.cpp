#include "function.h"

#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

Function :: Function(GLuint newShaderProgram, GLint new_size) : shaderProgram(newShaderProgram), size(new_size), input_size(0), x_centre(0), y_centre(0){



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

void Function :: set_centre(double new_x_centre, double new_y_centre) {
    x_centre = new_x_centre;
    y_centre = new_y_centre;

}

void Function :: update_vertices() {
    vertices.clear();
    int adjustment = 0;
    if (x_centre < 0) {
        adjustment = -x_centre;
    } else {
        adjustment = x_centre;
    }
    if (input_size != 0) {

        for (double i = -size - adjustment - 1; i <= size + adjustment + 1; i+=0.01*sqrt(size)) {
            float x = (static_cast<float>(i + x_centre))/(static_cast<float>(size));
            vertices.push_back(x);
            vertices.push_back(static_cast<float>(evaluate(i, input) + y_centre) / (static_cast<float>(size)));
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
    input += new_input;
    input_size = input.size();
}

string Function :: get_input() {
    return input;
}

vector<CustomInput> Function :: get_custom_vector(double x, string new_input) {
    vector<CustomInput> v;
    bool first = true;
    bool make_negative = false;

    CustomInput start_input;
    start_input.type = Type::Number;
    start_input.number = 0.0;
    start_input.operation = 0.0;
    v.push_back(start_input);

    CustomInput start_input2;
    start_input2.type = Type::Operator;
    start_input2.number = 0.0;
    start_input2.operation = '+';
    v.push_back(start_input2);
    for (int i = 0; i < new_input.size(); i++) {

        if (new_input[i] != ' ' && new_input[i] != '-') {
            first = false;
        }
        if (new_input[i] >= '0' && new_input[i] <= '9') {
            double number = new_input[i] - '0';
            bool keep_going = true;
            while (i + 1 < new_input.size() && keep_going) {
                if (new_input[i + 1] >= '0' && new_input[i + 1] <= '9') {
                    number *= 10.0;
                    number += (new_input[i + 1] - '0');
                } else if (new_input[i + 1] == 'x') {
                    number *= x;
                } else if (new_input[i + 1] == '.') {
                    double decimal_rate = 10.0;
                    while (i + 2 < new_input.size() && new_input[i + 2] >= '0' && new_input[i + 2] <= '9') {
                        number += ((new_input[i + 2] - '0') / decimal_rate);
                        decimal_rate *= 10.0;
                        i++;
                    }
                } else {
                    keep_going = false;
                    i--;
                }
                i++;
            }
            if (make_negative) {
                number *= -1.0;
                make_negative = false;
            }
            CustomInput input;
            input.type = Type::Number;
            input.number = number;
            input.operation = 0.0;
            v.push_back(input);

        } else if (new_input[i] == 'x') {
            CustomInput input;
            input.type = Type::Number;
            if (make_negative) {
                input.number = -1.0 * x;
                make_negative = false;
            } else {
                input.number = x;
            }
            input.operation = 0.0;
            v.push_back(input);
        } else if (new_input[i] == '*') {
            CustomInput input;
            input.type = Type::Operator;
            input.number = 0.0;
            input.operation = '*';
            v.push_back(input);
        } else if (new_input[i] == '/') {
            CustomInput input;
            input.type = Type::Operator;
            input.number = 0.0;
            input.operation = '/';
            v.push_back(input);
        } else if (new_input[i] == '+') {
            CustomInput input;
            input.type = Type::Operator;
            input.number = 0.0;
            input.operation = '+';
            v.push_back(input);
        } else if (new_input[i] == '-') {

            if ((new_input[i - 1] == '+' || new_input[i - 1] == '/' || new_input[i - 1] == '-' || new_input[i-1] == '(' || new_input[i-1] == '*') && !first) {
                make_negative  = true;
            } else {
                if (first) {
                    v.erase(v.begin() + 1, v.begin() + 2);
                }
                CustomInput input;
                input.type = Type::Operator;
                input.number = 0.0;
                input.operation = '-';
                v.push_back(input);
            }
        } else if (new_input[i] == '^') {
            CustomInput input;
            input.type = Type::Operator;
            input.number = 0.0;
            input.operation = '^';
            v.push_back(input);
        } else if (new_input[i] == '(') {
            CustomInput input;
            input.type = Type::Operator;
            input.number = 0.0;
            input.operation = '(';
            v.push_back(input);
        } else if (new_input[i] == ')') {
            CustomInput input;
            input.type = Type::Operator;
            input.number = 0.0;
            input.operation = ')';
            v.push_back(input);
        } else if (new_input[i] == 's') {
            if (i + 2 < new_input.size() && new_input[i + 1] == 'i' && new_input[i + 2] == 'n') {
                CustomInput input;
                input.type = Type::Operator;
                input.number = 0.0;
                input.operation = 's';
                v.push_back(input);
                i += 2;
            }
        }
    }

    return v;
}

double Function :: calculate(double num1, double num2, char operation) {
    if (operation == '+') {
        return num1 + num2;
    } else if (operation == '-') {
        return num1 - num2;
    } else if (operation == '*') {
        return num1 * num2;
    } else if (operation == '/') {
        return num1 / num2;
    } else if (operation == '^') {
        return pow(num1, num2);
    } else if (operation == 's') {
        return sin(num1);
    }
}

double Function :: evaluate(double x, string new_input, vector<CustomInput> brackets_vector, bool brackets) {
    vector<CustomInput> custom_vector;
    if (!brackets) {
        custom_vector = get_custom_vector(x, new_input);
    } else {
        custom_vector = brackets_vector;
    }

    for (int i = 0; i < custom_vector.size(); i++) {
        if (custom_vector[i].operation == '(') {
            int depth = 1;
            for (int j = i + 1; j < custom_vector.size(); j++) {
                if (custom_vector[j].operation == '(') {
                    depth++;
                }
                if (custom_vector[j].operation == ')') {
                    depth--;
                    if (depth == 0) {
                        vector<CustomInput> sub_custom_vector(custom_vector.begin() + i + 1, custom_vector.begin() + j);
                        double result = evaluate(x, " ", sub_custom_vector, true);
                        custom_vector[i] = CustomInput {Type::Number, result, 0};
                        custom_vector.erase(custom_vector.begin() + i + 1, custom_vector.begin() + j +  1);
                        i--;
                        break;
                    }

                }
            }
        }
    }

    for (int i = 0; i < custom_vector.size(); i++) {
        if (custom_vector[i].operation == 's') {
            if (i + 1 < custom_vector.size()) {
                double result = calculate(custom_vector[i+1].number, 0, custom_vector[i].operation);
                custom_vector[i] = CustomInput {Type::Number, result, 0};
                custom_vector.erase(custom_vector.begin() + i + 1);
                i--;
            }
        }
    }

    for (int i = 0; i < custom_vector.size(); i++) {
        if (custom_vector[i].operation == '^') {
            if (i + 1 < custom_vector.size()) {
                double result = calculate(custom_vector[i-1].number, custom_vector[i+1].number, custom_vector[i].operation);
                custom_vector[i-1] = CustomInput {Type::Number, result, 0};
                custom_vector.erase(custom_vector.begin() + i, custom_vector.begin() + i + 2);
                i--;
            }
        }
    }

    for (int i = 0; i < custom_vector.size(); i++) {
        if (custom_vector[i].operation == '*' || custom_vector[i].operation == '/') {
            if (i + 1 < custom_vector.size()) {
                double result = calculate(custom_vector[i-1].number, custom_vector[i+1].number, custom_vector[i].operation);
                custom_vector[i-1] = CustomInput {Type::Number, result, 0};
                custom_vector.erase(custom_vector.begin() + i, custom_vector.begin() + i + 2);
                i--;
            }
        }
    }

    for (int i = 0; i < custom_vector.size(); i++) {
        if (custom_vector[i].operation == '+' || custom_vector[i].operation == '-') {
            if (i + 1 < custom_vector.size()) {
                double result = calculate(custom_vector[i-1].number, custom_vector[i+1].number, custom_vector[i].operation);
                custom_vector[i-1] = CustomInput {Type::Number, result, 0};
                custom_vector.erase(custom_vector.begin() + i, custom_vector.begin() + i + 2);
                i--;
            }
        }
    }

    return custom_vector[0].number;
}

