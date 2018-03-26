#pragma once

#include <glad/glad.h>

class Triangle  // NOLINT
{
public:
	float vertices[9];
	GLuint vao;
	bool isInitialized;

	void Init();
	void Draw() const;
	explicit Triangle(const float* vertices, bool initialize = true);
	~Triangle();
};