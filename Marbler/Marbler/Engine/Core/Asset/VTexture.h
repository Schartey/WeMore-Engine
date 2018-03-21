#pragma once

#include <string>

#include "GL\glew.h"
#include "IL/il.h"

class VTexture
{
public:
	VTexture(std::string name);

	GLuint GetId();
	bool Load();

	void Bind(GLenum TextureUnit);

	~VTexture();

private:
	std::string fileName1;
	GLuint Id;
};

