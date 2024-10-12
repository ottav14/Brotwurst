#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

GLuint createShaderProgram(GLfloat* vertices, size_t vertices_size, const char* vertexShaderSource, const char* fragmentShaderSource, GLuint* VAO, GLuint* VBO);
GLfloat* generateVertices(size_t* vertices_size);

#endif
