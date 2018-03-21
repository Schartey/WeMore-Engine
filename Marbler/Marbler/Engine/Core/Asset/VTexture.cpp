#include "VTexture.h"

#include "VImage.h"

VTexture::VTexture(std::string name)
{
	this->fileName1 = name;
}

GLuint VTexture::GetId()
{
	return Id;
}

bool VTexture::Load() {


	VImage* Image = new VImage(fileName1);
	if (!Image->Load())
	{
		return false;
	}

	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_2D, Id);

	glTexImage2D(GL_TEXTURE_2D, 0, Image->GetFormat(), Image->GetWidth(), Image->GetHeight(), 0, Image->GetFormat(), Image->GetType(), Image->GetData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glGenerateMipmap(GL_TEXTURE_2D);

	delete Image;
}

void VTexture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_2D, this->GetId());
}

VTexture::~VTexture()
{
}
