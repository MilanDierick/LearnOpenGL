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

	const auto renderer = glGetString(GL_RENDERER);
	const auto version = glGetString(GL_VERSION);
	printf("Renderer: %p\n", renderer);
	printf("OpenGL version supported %p\n", version);
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


	float vertices1[] = {
		-1.0f, -0.5f, 0.0f, // left  
		0.0f, -0.5f, 0.0f, // right 
		-0.5f,  0.5f, 0.0f  // top   
	};

	float vertices2[] = {
		0.0f, -0.5f, 0.0f, // left  
		1.0f, -0.5f, 0.0f, // right 
		0.5f,  0.5f, 0.0f  // top  
	};

	const auto triangle1 = new Triangle(vertices1);
	const auto triangle2 = new Triangle(vertices2);


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
		// Input
		processInput(window->getWindow());

		// Rendering
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		// Changing color over time
		const float timeValue = glfwGetTime();
		const float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		const int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		triangle1->Draw();
		triangle2->Draw();
		
		// Check and call events and swap the buffers.
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
	
	delete window;
	delete triangle1;
	delete triangle2;

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
