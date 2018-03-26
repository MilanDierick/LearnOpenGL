#include "Triangle.h"

float* Triangle::getVertices() const
{
	return vertices;
}

void Triangle::setVertices(float* const vertices)
{
	this->vertices = vertices;
}

GLuint Triangle::getVao() const
{
	return vao;
}

void Triangle::setVao(const GLuint vao)
{
	this->vao = vao;
}

GLuint Triangle::getVbo() const
{
	return vbo;
}

void Triangle::setVbo(const GLuint vbo)
{
	this->vbo = vbo;
}

Triangle::Triangle(float* vertices, const GLuint vao, const GLuint vbo)
{
	this->vertices = vertices;
	this->vao = vao;
	this->vbo = vbo;

	glGenBuffers(1, &this->vbo);
	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
