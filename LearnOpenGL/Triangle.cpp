#include "Triangle.h"

float* Triangle::getVertices()
{
	return vertices;
}

void Triangle::setVertices(const float* vertices)
{
	for (auto x = 0; x < 12; ++x)
		this->vertices[x] = vertices[x];
}

GLuint Triangle::getVbo() const
{
	return vbo;
}

void Triangle::setVbo(const GLuint vbo)
{
	this->vbo = vbo;
}

Triangle::Triangle(const float* vertices, const GLuint &vao)
{
	for (auto x = 0; x < 12; ++x)
	{
		this->vertices[x] = vertices[x];
	}

	glGenBuffers(1, &this->vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Triangle::~Triangle()
{
	glDeleteBuffers(1, &vbo);
}
