#include "graphics.h"

GLuint createShaderProgram(GLfloat* vertices, size_t vertices_size, const char* vertexShaderSource, const char* fragmentShaderSource, GLuint* VAO, GLuint* VBO) {

    // Create a Vertex Buffer Object (VBO) and a Vertex Array Object (VAO)
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    // Bind the Vertex Array Object first, then bind and set the vertex buffer(s)
    glBindVertexArray(*VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    // Then set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO (it's a good practice to unbind it when we're done)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    GLint success;

    // Compile Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for compilation errors
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    // Compile Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    // Link shaders into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders as they're no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLfloat* generateVertices(size_t* vertices_size) {

	GLfloat _vertices[] = {
		-1.0f,  1.0f,  0.0f,  // Top-left
		1.0f,  1.0f,  0.0f,  // Top-right
		-1.0f, -1.0f,  0.0f,  // Bottom-left
		1.0f, -1.0f,  0.0f   // Bottom-right
	};

	*vertices_size = sizeof(_vertices);
	GLfloat* vertices = (GLfloat*)malloc(*vertices_size);
	for(size_t i = 0; i < *vertices_size/sizeof(GLfloat); i++)
		vertices[i] = _vertices[i];

	return vertices;
	
}


