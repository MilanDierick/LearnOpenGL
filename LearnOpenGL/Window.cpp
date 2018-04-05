#include "Window.h"
#include <utility>
#include <iostream>
#include <glad/glad.h>

int Window::getWidth() const
{
	return width_;
}

void Window::setWidth(const int width)
{
	this->width_ = width;
}

int Window::getHeight() const
{
	return height_;
}

void Window::setHeight(const int height)
{
	this->height_ = height;
}

std::string Window::getTitle() const
{
	return title_;
}

void Window::setTitle(const std::string& title)
{
	this->title_ = title;
}

GLFWmonitor* Window::getMonitor() const
{
	return monitor_;
}

void Window::setMonitor(GLFWmonitor* const monitor)
{
	this->monitor_ = monitor;
}

GLFWwindow* Window::getWindow() const
{
	return window_;
}

void Window::setWindow(GLFWwindow* const window)
{
	this->window_ = window;
}

bool Window::getIsCreated() const
{
	return isCreated_;
}

void Window::setIsCreated(const bool isCreated)
{
	this->isCreated_ = isCreated;
}

void Window::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
	std::cout << "Viewport changed: (" << width << "," << height << ")." << std::endl;
	glViewport(0, 0, width, height);
}

Window::Window(const int width, int const height, std::string title, GLFWmonitor* monitor,
               GLFWwindow* const window): width_(width),
                                                                height_(height),
                                                                title_(std::move(title)),
                                                                monitor_(monitor),
                                                                window_(window)
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
		isCreated_ = false;
		glfwTerminate();
		throw;
	}

	glfwMakeContextCurrent(this->getWindow());
	glViewport(0, 0, this->getWidth(), this->getHeight());
	glfwSetFramebufferSizeCallback(this->getWindow(), FramebufferSizeCallback);

	isCreated_ = true;
}
