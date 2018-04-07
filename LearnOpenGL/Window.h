#pragma once

#include "CommonHeader.h"

class Window
{
	// TODO: Get rid of all the getters and setter, they are no longer needed. 
public:
	int GetWidth() const;
	void SetWidth(const int width);
	int GetHeight() const;
	void SetHeight(const int height);
	std::string GetTitle() const;
	void SetTitle(const std::string& title);
	GLFWmonitor* GetMonitor() const;
	void SetMonitor(GLFWmonitor* const monitor);
	GLFWwindow* GetWindow() const;
	void SetWindow(GLFWwindow* const window);
	bool GetIsCreated() const;
	void SetIsCreated(const bool isCreated);
	Window(int width, int height, std::string title, GLFWmonitor* monitor,
	       GLFWwindow* window);


private:
	int width;
	int height;
	std::string title;
	GLFWmonitor* monitor;
	GLFWwindow* window;
	bool isCreated;
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};
