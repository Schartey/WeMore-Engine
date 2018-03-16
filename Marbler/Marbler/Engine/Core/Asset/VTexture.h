#pragma once

#include <string>

#include "GL\glew.h"
#include "IL/il.h"

class VTexture
{
public:
	VTexture();

	int GetId();
	GLuint LoadTextureFromFile(std::string name);

	~VTexture();

private:
	int Id;

	GLuint LoadImage(const char* path);
};

