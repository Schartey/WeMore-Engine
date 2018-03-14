#pragma once

#include <string>

#include "GL\glew.h"
#include "IL/il.h"

class VTexture
{
public:
	VTexture();

	GLuint LoadTextureFromFile(std::string name, std::string path);

	~VTexture();

private:
	int Id;

	GLuint LoadImage(const char* path);
};

