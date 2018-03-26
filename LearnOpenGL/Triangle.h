#pragma once

#include <glad/glad.h>

class Triangle
{
public:
	float* getVertices() const;
	void setVertices(float* const vertices);
	GLuint getVao() const;
	void setVao(const GLuint vao);
	GLuint getVbo() const;
	void setVbo(const GLuint vbo);
	Triangle(float* vertices, GLuint vao, GLuint vbo);

private:
	float *vertices;
	GLuint vao;
	GLuint vbo;
};
