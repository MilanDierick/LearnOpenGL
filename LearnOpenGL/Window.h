#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public:

	int getWidth() const;
	void setWidth(const int width);
	int getHeight() const;
	void setHeight(const int height);
	std::string getTitle() const;
	void setTitle(const std::string& title);
	GLFWmonitor* getMonitor() const;
	void setMonitor(GLFWmonitor* const monitor);
	GLFWwindow* getWindow() const;
	void setWindow(GLFWwindow* const window);
	bool getIsCreated() const;
	void setIsCreated(const bool isCreated);
	Window(int width, int height, std::string title, GLFWmonitor* monitor,
	       GLFWwindow* window);
	

private:
	int width;
	int height;
	std::string title;
	GLFWmonitor *monitor;
	GLFWwindow *window;
	bool isCreated;
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};
