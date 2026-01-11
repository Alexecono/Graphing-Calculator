

#ifndef AXIS_H
#define AXIS_H


#include <vector>
#include <glad/glad.h>

class Axis {
    public:
    Axis(GLuint newShaderProgram, GLuint new_size);
    ~Axis();
    void draw() const;
    void update_vertices();
    void update_axis();
    void set_centre(double new_x_centre, double new_y_centre);
    void set_size(GLint new_size);

    private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint shaderProgram, size;
    std::vector <float> vertices;
    double x_centre;
    double y_centre;

};
#endif //AXIS_H