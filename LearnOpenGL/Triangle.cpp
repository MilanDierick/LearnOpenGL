#include "Triangle.h"
#include <iostream>
#include <gl/GL.h>

void Triangle::Init()
{
	if (!isInitialized)
	{
		GLuint vbo;

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		isInitialized = true;
	}
}
void Triangle::Draw() const
{
	if (isInitialized)
	{
		glBindVertexArray(this->vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	else
	{
		std::cout << "ERROR::TRIANGLE::DRAW::UNINITIALIZED_OBJECT_DRAW" << std::endl;
	}
}

Triangle::Triangle(const float* vertices, const bool initialize): vao(0), isInitialized(false)  // NOLINT
{
	for (auto x = 0; x < 18; ++x)
	{
		this->vertices[x] = vertices[x];
	}

	if (initialize)
		Init();
	else
		std::cout << "WARNING::TRIANGLE::INIT::UNINITIALIZED_OBJECT" << std::endl;
}

Triangle::~Triangle()
{
	glDeleteBuffers(1, &vao);
}
