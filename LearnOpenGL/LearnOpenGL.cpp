// LearnOpenGL.cpp : Defines the entry point for the console application.

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CommonHeader.h"

#include "Window.h"
#include "Triangle.h"
#include "Shader.h"

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
	const auto shader = new Shader("vertexShader.vert", "fragmentShader.frag");

	float vertices[] = {
		-1.0f,  1.0f, 0.0f, // Top-left
		1.0f,  1.0f, 0.0f, // Top-right
		1.0f, -1.0f, 0.0f, // Bottom-right
	
		1.0f, -1.0f, 0.0f, // Bottom-right
		-1.0f, -1.0f, 0.0f, // Bottom-left
		-1.0f,  1.0f, 0.0f  // Top-left
	};

	const auto triangle1 = new Triangle(vertices);
	shader->Use();
// TODO: move game loop to seperate class
	while (!glfwWindowShouldClose(window->GetWindow()))
	{
		CURRENT_TIME = glfwGetTime();
		DELTA_TIME = CURRENT_TIME - LAST_TIME;
		LAST_TIME = CURRENT_TIME;
	
		auto windowWidth = 0;
		auto windowHeight = 0;
		glfwGetWindowSize(window->GetWindow(), &windowWidth, &windowHeight);
	
		// Input
		processInput(window->GetWindow());
	
		if (CURRENT_TIME - RENDER_LAST_TIME > 0.016)
		{
			// Rendering
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
	
			// Changing color over time
			auto mousePosX = 0.0;
			auto mousePosY = 0.0;
			glfwGetCursorPos(window->GetWindow(), &mousePosX, &mousePosY);
			//shader->Use();
			shader->SetVec2("u_location", window->GetWidth(), window->GetHeight());
			shader->SetFloat("u_time", CURRENT_TIME);
	
			triangle1->Draw();
	
			glfwSwapBuffers(window->GetWindow());
			RENDER_LAST_TIME = glfwGetTime();
		}
	
		// Check and call events and swap the buffers.
		glfwPollEvents();
	}
	
	delete window;
	delete triangle1;
	delete shader;

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
