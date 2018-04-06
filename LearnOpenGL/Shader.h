#pragma once
#ifndef SHADER_H
#define SHADER_H

#define INFO_LOG_BUFFER 512

#include <glad/glad.h> // Include glad to get all the required OpenGL header

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	
	/**
	 * \brief The program ID.
	 */
	GLuint id;

	/**
	 * \brief Constructor reads and builds the shader.
	 * \param vertexPath The path to the vertex shader.
	 * \param fragmentPath The path to the fragment shader.
	 */
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	/**
	 * \brief Use/activate the shader.
	 */
	void Use() const;

	/**
	 * \brief Utility uniform funtion.
	 * \param name Name of the uniform.
	 * \param value Value of the uniform.
	 */
	void SetBool(const std::string &name, bool value) const;

	/**
	* \brief Utility uniform funtion.
	* \param name Name of the uniform.
	* \param value Value of the uniform.
	*/
	void SetInt(const std::string &name, int value) const;

	/**
	* \brief Utility uniform funtion.
	* \param name Name of the uniform.
	* \param value Value of the uniform.
	*/
	void SetFloat(const std::string &name, float value) const;

	/**
	 * \brief Utility uniform function.
	 * \param name Name of the uniform.
	 * \param value1 Value of the first vector component.
	 * \param value2 Value of the second vector component.
	 */
	void SetVec2(const std::string &name, float value1, float value2) const;
};

#endif