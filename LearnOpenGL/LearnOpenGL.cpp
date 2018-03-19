// LearnOpenGL.cpp : Defines the entry point for the console application.
//

#include <glad/glad.h>
#include <iostream>
#include "Window.h"
#include "shaderSource.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void processInput(GLFWwindow* window);

int main()
{
	glfwInit();

	const auto window = new Window{ WINDOW_WIDTH, WINDOW_HEIGHT, "Learning OpenGL", nullptr, nullptr };
	ShaderSources shaderSources{};

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


// TODO: move triangle configuration to seperate class.
	// Start the configuration to draw a triangle.
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,

		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// TODO: move shader compilation to seperate file/class.
	const auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSources.vertexShaderSource, nullptr);

// TODO: move game loop to seperate class
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		// Input
		processInput(window->getWindow());

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Check and call events and swap the buffers.
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
	
	delete window;

	glfwTerminate();
    return 0;
}

// TODO: move input processing to game loop class.
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);
}
