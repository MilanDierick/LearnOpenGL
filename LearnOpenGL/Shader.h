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
	void Use();

	/**
	 * \brief Utility uniform funtion.
	 * \param name Name of the uniform.
	 * \param value Value of the uniform.
	 */
	void SetBool(const std::string &name, bool value);

	/**
	* \brief Utility uniform funtion.
	* \param name Name of the uniform.
	* \param value Value of the uniform.
	*/
	void SetInt(const std::string &name, int value);

	/**
	* \brief Utility uniform funtion.
	* \param name Name of the uniform.
	* \param value Value of the uniform.
	*/
	void SetFloat(const std::string &name, int value);
};

#endif