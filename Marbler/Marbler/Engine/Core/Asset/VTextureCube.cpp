#include "VTextureCube.h"

#include "VImage.h"

GLuint VTextureCube::TextureCubeTypes[] = { 
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

VTextureCube::VTextureCube(const std::string& fileName1,
	const std::string& fileName2,
	const std::string& fileName3,
	const std::string& fileName4,
	const std::string& fileName5,
	const std::string& fileName6)
{
	this->fileName[0] = fileName1;
	this->fileName[1] = fileName2;
	this->fileName[2] = fileName3;
	this->fileName[3] = fileName4;
	this->fileName[4] = fileName5;
	this->fileName[5] = fileName6;
}

GLuint VTextureCube::GetId()
{
	return Id;
}

bool VTextureCube::Load()
{
	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Id);

	VImage* Images[6];

	for (int i = 0; i < sizeof(Images) / sizeof(VImage*); i++)
	{
		Images[i] = new VImage(this->fileName[i]);

		if (!Images[i]->Load())
		{
			return false;
		}
		glTexImage2D(TextureCubeTypes[i], 0, Images[i]->GetFormat(), Images[i]->GetWidth(), Images[i]->GetHeight(), 0, Images[i]->GetFormat(), Images[i]->GetType(), Images[i]->GetData());

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		delete Images[i];
	}

	return true;
}

void VTextureCube::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, this->GetId());
}

VTextureCube::~VTextureCube()
{
}
