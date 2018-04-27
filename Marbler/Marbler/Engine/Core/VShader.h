#pragma once

#include <string>
#include <GL\glew.h>

class VShader
{
public:
	GLuint programHandle;

	VShader(const std::string& computeShader);
	VShader(const std::string& vertexShader, const std::string& fragmentShader);
	VShader(const std::string& vertexShader, const std::string& geometryShader, const std::string& fragmentShader);

	void useShader() const;

	~VShader();

private:
	void loadShader(const std::string& shader, GLenum shaderType, GLuint& handle);
	void link();

	enum ProgramType { VertexFragment, Compute };
	GLuint vertexHandle;
	GLuint geometryHandle;
	GLuint fragmentHandle;
	GLuint computeHandle;

	ProgramType programType;
};