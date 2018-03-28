// LearnOpenGL.cpp : Defines the entry point for the console application.
//

#include <glad/glad.h>
#include <iostream>
#include "Window.h"
#include "shaderSource.h"
#include "Triangle.h"
#include <complex>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define LOG_MAX_BUFFER 512

void processInput(GLFWwindow* window);

double DELTA_TIME = 0.0;
double CURRENT_TIME = 0.0;
double LAST_TIME = 0.0;
double RENDER_LAST_TIME = 0.0;

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

	const auto renderer = glGetString(GL_RENDERER);
	const auto version = glGetString(GL_VERSION);
	printf("Renderer: %p\n", renderer);
	printf("OpenGL version supported %p\n", version);
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	float vertices[] = {
		-1.0f,  1.0f, 0.0f, // Top-left
		1.0f,  1.0f, 0.0f, // Top-right
		1.0f, -1.0f, 0.0f, // Bottom-right

		1.0f, -1.0f, 0.0f, // Bottom-right
		-1.0f, -1.0f, 0.0f, // Bottom-left
		-1.0f,  1.0f, 0.0f  // Top-left
	};

	float vertices1[] = {
		-1.0f, -1.0f, 0.0f, // left  
		1.0f, -1.0f, 0.0f, // right 
		0.0f,  1.0f, 0.0f  // top   
	};

	/*
	 * 	float vertices1[] = {
		-1.0f, -0.5f, 0.0f, // left  
		0.0f, -0.5f, 0.0f, // right 
		-0.5f,  0.5f, 0.0f  // top   
	};
	 */

	float vertices2[] = {
		0.0f, -0.5f, 0.0f, // left  
		1.0f, -0.5f, 0.0f, // right 
		0.5f,  0.5f, 0.0f  // top  
	};

	const auto triangle1 = new Triangle(vertices);
	//const auto triangle2 = new Triangle(vertices2);

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
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, LOG_MAX_BUFFER, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

// TODO: move game loop to seperate class
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		CURRENT_TIME = glfwGetTime();
		DELTA_TIME = CURRENT_TIME - LAST_TIME;
		LAST_TIME = CURRENT_TIME;

		// Input
		processInput(window->getWindow());

		if (CURRENT_TIME - RENDER_LAST_TIME > 0.016)
		{
			// Rendering
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(shaderProgram);

			// Changing color over time
			auto mousePosX = 0.0;
			auto mousePosY = 0.0;
			glfwGetCursorPos(window->getWindow(), &mousePosX, &mousePosY);

			const auto resolutionLocation = glGetUniformLocation(shaderProgram, "u_resolution");
			const auto timeLocation = glGetUniformLocation(shaderProgram, "u_time");
			const auto mouseLocation = glGetUniformLocation(shaderProgram, "u_mouse");
			glUniform2f(resolutionLocation, WINDOW_WIDTH, WINDOW_HEIGHT); // TODO: make this dynamically change when size of viewport changes.
			glUniform1f(timeLocation, CURRENT_TIME);
			glUniform2f(mouseLocation, mousePosX, mousePosY);

			triangle1->Draw();
			//triangle2->Draw();

			glfwSwapBuffers(window->getWindow());
			RENDER_LAST_TIME = glfwGetTime();
		}

		// Check and call events and swap the buffers.
		glfwPollEvents();
	}
	
	delete window;
	delete triangle1;
	//delete triangle2;

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
