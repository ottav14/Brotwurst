#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graphics.h"
#include "util.h"

GLFWwindow* window;
GLuint VBO, VAO;

void init() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
    // Get the primary monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        fprintf(stderr, "Failed to get primary monitor\n");
        glfwTerminate();
        return;
    }

    // Get the video mode of the monitor
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (!mode) {
        fprintf(stderr, "Failed to get video mode\n");
        glfwTerminate();
        return;
    }

    // Create a fullscreen window
    window = glfwCreateWindow(mode->width, mode->height, "Fullscreen Window", monitor, NULL);
    if (!window) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
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

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input (optional)
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // Swap buffers and poll events
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

