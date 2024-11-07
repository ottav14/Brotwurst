#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "graphics.h"
#include "util.h"

#define MOVE_SPEED 0.02
#define ZOOM_SPEED 0.015

GLFWwindow* window;
GLuint VBO, VAO;
double u_position_x = 0;
double u_position_y = 0;
double desired_position_x = 0;
double desired_position_y = 0;
double u_zoom = 1;
double desired_zoom = 1;

void handle_input(GLFWwindow* window) {
	// Quit
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Movement controls
	double x_offset = 0;
	double y_offset = 0;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		y_offset += 1;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		x_offset -= 1;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		y_offset -= 1;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		x_offset += 1;

	double mag = sqrt(x_offset*x_offset + y_offset*y_offset);
	if(mag > 0) {
		desired_position_x += u_zoom * MOVE_SPEED * x_offset / mag;
		desired_position_y += u_zoom * MOVE_SPEED * y_offset / mag;
	}

	u_position_x = lerp(u_position_x, desired_position_x, 0.05); 
	u_position_y = lerp(u_position_y, desired_position_y, 0.05); 


	// Zoom controls
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		desired_zoom *= 1.0 - ZOOM_SPEED;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		desired_zoom *= 1.0 + ZOOM_SPEED;

	u_zoom = lerp(u_zoom, desired_zoom, 0.05);

}

void update_uniforms(GLuint shaderProgram) {

	GLint positionLocation = glGetUniformLocation(shaderProgram, "u_position");
	glUniform2f(positionLocation, u_position_x, u_position_y);

	GLint zoomLocation = glGetUniformLocation(shaderProgram, "u_zoom");
	glUniform1f(zoomLocation, u_zoom);

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
	update_uniforms(shaderProgram);

    // Main loop
    while (!glfwWindowShouldClose(window)) {

		handle_input(window);

		update_uniforms(shaderProgram);

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

