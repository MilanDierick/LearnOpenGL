#include "Window.h"
#include <utility>
#include <iostream>
#include <glad/glad.h>

int Window::GetWidth() const
{
	return width;
}

void Window::SetWidth(const int width)
{
	this->width = width;
}

int Window::GetHeight() const
{
	return height;
}

void Window::SetHeight(const int height)
{
	this->height = height;
}

std::string Window::GetTitle() const
{
	return title;
}

void Window::SetTitle(const std::string& title)
{
	this->title = title;
}

GLFWmonitor* Window::GetMonitor() const
{
	return monitor;
}

void Window::SetMonitor(GLFWmonitor* const monitor)
{
	this->monitor = monitor;
}

GLFWwindow* Window::GetWindow() const
{
	return window;
}

void Window::SetWindow(GLFWwindow* const window)
{
	this->window = window;
}

bool Window::GetIsCreated() const
{
	return isCreated;
}

void Window::SetIsCreated(const bool isCreated)
{
	this->isCreated = isCreated;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
	std::cout << "Viewport changed: (" << width << "," << height << ")." << std::endl;
	glViewport(0, 0, width, height);
}

Window::Window(const int width, int const height, std::string title, GLFWmonitor* monitor,
               GLFWwindow* const window): width(width),
                                                                height(height),
                                                                title(std::move(title)),
                                                                monitor(monitor),
                                                                window(window)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	this->SetWindow(glfwCreateWindow(this->GetWidth(), this->GetHeight(), this->GetTitle().c_str(), this->GetMonitor(),
	                                 this->GetWindow()));

	if (this->GetWindow() == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		isCreated = false;
		glfwTerminate();
		throw;
	}

	glfwMakeContextCurrent(this->GetWindow());
	glfwSetFramebufferSizeCallback(this->GetWindow(), FramebufferSizeCallback);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::cin.get();
		throw;
	}

	glViewport(0, 0, this->GetWidth(), this->GetHeight());

	const auto renderer = glGetString(GL_RENDERER);
	const auto version = glGetString(GL_VERSION);
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported: " << version << std::endl;
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	isCreated = true;
}
