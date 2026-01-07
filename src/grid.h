
#ifndef GRID_H
#define GRID_H

#include <glad/glad.h>
#include <vector>
using namespace std;

class Grid {
public:
    Grid(GLuint newShaderProgram, GLint new_size);
    ~Grid();
    void draw() const;
    void set_size(GLint new_size);
    void update_vertices();
    void update_grid();

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint shaderProgram, size;
    vector <float> vertices;

};
#endif //GRID_H