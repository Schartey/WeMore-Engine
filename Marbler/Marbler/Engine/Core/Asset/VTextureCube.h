#pragma once

#include <string>
#include "GL/glew.h"

class VTextureCube
{
public:
	VTextureCube(const std::string& fileName1, 
		const std::string& fileName2,
		const std::string& fileName3,
		const std::string& fileName4,
		const std::string& fileName5,
		const std::string& fileName6);

	GLuint GetId();
	bool Load();

	void Bind(GLenum TextureUnit);

	~VTextureCube();

private:
		
	static GLuint TextureCubeTypes[];

	std::string fileName[6];
	GLuint Id;

};

