// LearnOpenGL.cpp : Defines the entry point for the console application.
//

#include <glad/glad.h>
#include <iostream>
#include "Window.h"
#include "shaderSource.h"
#include "Triangle.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define LOG_MAX_BUFFER 512

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

	GLuint vao;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};

	glGenVertexArrays(1, &vao);

	const auto triangle = new Triangle(vertices, vao);


// TODO: move shader compilation to seperate file/class.
	int success;
	char infoLog[LOG_MAX_BUFFER];

	const auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderSources.vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, LOG_MAX_BUFFER, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderSources.fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, LOG_MAX_BUFFER, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const auto shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, LOG_MAX_BUFFER, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

//	glUseProgram(shaderProgram);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);

// TODO: move game loop to seperate class
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		// Input
		processInput(window->getWindow());

		// Rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindVertexArray(0); // No need to unbind it every single frame.
		
		// Check and call events and swap the buffers.
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
	
	delete window;
	delete triangle;

	glDeleteVertexArrays(1, &vao);

	glfwTerminate();
    return 0;
}

// TODO: move input processing to game loop class.
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_P))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_F))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
