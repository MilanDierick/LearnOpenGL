#include "Window.h"
#include <utility>
#include <iostream>

int Window::getWidth() const
{
	return width;
}

void Window::setWidth(const int width)
{
	this->width = width;
}

int Window::getHeight() const
{
	return height;
}

void Window::setHeight(const int height)
{
	this->height = height;
}

std::string Window::getTitle() const
{
	return title;
}

void Window::setTitle(const std::string& title)
{
	this->title = title;
}

GLFWmonitor* Window::getMonitor() const
{
	return monitor;
}

void Window::setMonitor(GLFWmonitor* const monitor)
{
	this->monitor = monitor;
}

GLFWwindow* Window::getWindow() const
{
	return window;
}

void Window::setWindow(GLFWwindow* const window)
{
	this->window = window;
}

bool Window::getIsCreated() const
{
	return isCreated;
}

void Window::setIsCreated(const bool isCreated)
{
	this->isCreated = isCreated;
}

void Window::framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
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

	this->setWindow(glfwCreateWindow(this->getWidth(), this->getHeight(), this->getTitle().c_str(), this->getMonitor(),
	                                 this->getWindow()));

	if (this->getWindow() == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		isCreated = false;
		glfwTerminate();
		throw;
	}

	glfwMakeContextCurrent(this->getWindow());
	glViewport(0, 0, this->getWidth(), this->getHeight());
	glfwSetFramebufferSizeCallback(this->getWindow(), framebufferSizeCallback);

	isCreated = true;
}
