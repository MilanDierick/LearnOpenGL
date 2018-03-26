#pragma once

#include <glad/glad.h>

// TODO: Split up creation and configuration of a triangle.
class Triangle
{
public:
	float* getVertices();
	void setVertices(const float* vertices);
	GLuint getVbo() const;
	void setVbo(const GLuint vbo);
	Triangle(const float* vertices, const GLuint &vao);
	~Triangle();
	Triangle(const Triangle& other) = delete;
	Triangle(Triangle&& other) noexcept = delete;
	Triangle& operator=(const Triangle& other) = delete;
	Triangle& operator=(Triangle&& other) noexcept = delete;

private:
	float vertices[12];
	GLuint vbo{};
};