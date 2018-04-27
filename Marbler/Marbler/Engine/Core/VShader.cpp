#include "VShader.h"

#include <iostream>
#include <fstream>
#include <memory>

VShader::VShader(const std::string& computeShader) : programHandle(0), programType(ProgramType::Compute)
{
	programHandle = glCreateProgram();
	if (programHandle == 0)
	{
		std::cerr << "Failed to create shader program." << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	loadShader(computeShader, GL_COMPUTE_SHADER, computeHandle);

	link();
}

VShader::VShader(const std::string& vertexShader, const std::string& fragmentShader) : programHandle(0)
, vertexHandle(0)
, fragmentHandle(0)
, programType(ProgramType::VertexFragment)
{
	programHandle = glCreateProgram();
	if (programHandle == 0)
	{
		std::cerr << "Failed to create shader program." << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	loadShader(vertexShader, GL_VERTEX_SHADER, vertexHandle);
	loadShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentHandle);

	link();
}

VShader::VShader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader) : programHandle(0)
, vertexHandle(0)
, geometryHandle(0)
, fragmentHandle(0)
, programType(ProgramType::VertexFragment)
{
	programHandle = glCreateProgram();
	if (programHandle == 0)
	{
		std::cerr << "Failed to create shader program." << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	loadShader(vertexShader, GL_VERTEX_SHADER, vertexHandle);
	loadShader(geometryShader, GL_GEOMETRY_SHADER, geometryHandle);
	loadShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentHandle);

	link();
}

VShader::~VShader()
{
	glDeleteProgram(programHandle);
	glDeleteShader(vertexHandle);
	glDeleteShader(fragmentHandle);
}

void VShader::useShader() const
{
	glUseProgram(programHandle);
}

void VShader::loadShader(const std::string& shader, GLenum shaderType, GLuint& handle)
{
	std::ifstream shaderFile(shader);

	if (shaderFile.good())
	{
		auto code = std::string(std::istreambuf_iterator<char>(shaderFile), std::istreambuf_iterator<char>());
		shaderFile.close();

		handle = glCreateShader(shaderType);
		if (handle == 0)
		{
			std::cerr << "Failed to create shader." << std::endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}

		auto codePtr = code.c_str();
		glShaderSource(handle, 1, &codePtr, nullptr);
		glCompileShader(handle);

		GLint succeeded;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &succeeded);
		if (!succeeded || !glIsShader(handle))
		{
			GLint logSize;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logSize);

			auto msg = std::make_unique<char[]>(logSize);
			glGetShaderInfoLog(handle, logSize, nullptr, msg.get());

			std::cerr << "Failed to compile shader" << std::endl << msg.get() << std::endl;
			system("PAUSE");
			msg.reset(nullptr);
			exit(EXIT_FAILURE);

		}
	}
	else
	{
		std::cerr << "Failed to open shader file: " << shader << std::endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
}

void VShader::link()
{
	if (programType == ProgramType::VertexFragment)
	{
		glAttachShader(programHandle, vertexHandle);
		glAttachShader(programHandle, fragmentHandle);

		glLinkProgram(programHandle);

	}
	else
	{
		glAttachShader(programHandle, computeHandle);

		glLinkProgram(programHandle);
	}
	GLint succeeded;

	glGetProgramiv(programHandle, GL_LINK_STATUS, &succeeded);
	if (!succeeded)
	{
		GLint logSize;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &logSize);

		auto msg = std::make_unique<char[]>(logSize);
		glGetProgramInfoLog(programHandle, logSize, nullptr, msg.get());

		std::cerr << "Failed to link program" << std::endl << msg.get() << std::endl;
		system("PAUSE");
		msg.reset(nullptr);
		exit(-1);

	}
}