#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath
	// ---------------------------------------------------------------------

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// Ensure ifstream objects can throw exeptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open files
		vShaderFile.open(vertexPath, std::ifstream::in);
		fShaderFile.open(fragmentPath, std::ifstream::in);
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		// Read file's bufer contents into stream
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// Convert
		vertexCode	 = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
		// ReSharper disable once CppDeclaratorNeverUsed
	catch (std::ifstream::failure &e)
	{
		std::cout << "ERROR::SHADER::FILE_NOTSUCCESFULLY_READ" << std::endl;
		throw;
	}

	const auto vShaderCode = vertexCode.c_str();
	const auto fShaderCode = fragmentCode.c_str();

	// 2. Compile shaders
	// ---------------------------------------------------------------------

	int succes;
	char infoLog[INFO_LOG_BUFFER];

	// Vertex shader
	const auto vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);

	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(vertex, INFO_LOG_BUFFER, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	// Fragment shader
	const auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);

	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(vertex, INFO_LOG_BUFFER, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	// Creation of shader program
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	// Print linking errors, if any
	glGetProgramiv(id, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(id, INFO_LOG_BUFFER, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they're linked into our program now are no longer required
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use() const
{
	glUseProgram(id);
}

void Shader::SetBool(const std::string& name, const bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Shader::SetInt(const std::string& name, const int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, const float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const float value1, const float value2) const
{
	glUniform2f(id, value1, value2);
}
