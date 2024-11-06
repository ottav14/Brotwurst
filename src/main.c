#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphics.h"
#include "util.h"

GLFWwindow* window;
GLuint VBO, VAO;

void handle_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void init() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    window = glfwCreateWindow(mode->width, mode->height, "Fullscreen Window", monitor, NULL);
    glfwMakeContextCurrent(window);

    glewInit();

}

int main() {


	init();

    // Create shader program
	char* fragSource = readFileToString("src/shader.frag");
	char* vertSource = readFileToString("src/shader.vert");
	size_t vertices_size;
   	GLfloat* vertices = generateVertices(&vertices_size);
    GLuint shaderProgram = createShaderProgram(vertices, vertices_size, vertSource, fragSource, &VAO, &VBO);
	glUseProgram(shaderProgram);

	// Get uniform locations
	GLint resolutionLocation = glGetUniformLocation(shaderProgram, "u_resolution");

	// Set uniform values
	glUniform2f(resolutionLocation, 1920.0, 1080.0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {

		handle_input(window);

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
	free(vertices);
	free(fragSource);
	free(vertSource);
    return 0;
}

