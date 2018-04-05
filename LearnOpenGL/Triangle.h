#pragma once

#include <glad/glad.h>

// TODO: create seperated class to draw a quad on the screen instead of combining 2 triangles.
class Triangle  // NOLINT
{
public:
	float vertices[18];
	GLuint vao;
	bool isInitialized;

	void Init();
	void Draw() const; // TODO: when moving the shaders to this class, make sure to pass all the required data for the uniforms to be updated properly.
	explicit Triangle(const float* vertices, bool initialize = true);
	~Triangle();
};