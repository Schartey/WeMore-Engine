#include "VImage.h"



VImage::VImage(std::string filePath)
{
	this->fileName = filePath;
}

bool VImage::Load()
{
	bool success;			// Create a flag to keep track of success/failure

	ILenum error;				// Create a flag to keep track of the IL error state

	ilGenImages(1, &imageID); 		// Generate the image ID
	ilBindImage(imageID); 			// Bind the image

	success = ilLoadImage(fileName.c_str()); 	// Load the image file
									// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		Data = ilGetData();
		if (!Data) {
			ilBindImage(0);
			ilDeleteImages(1, &imageID);
			return false;
		}

		Width = ilGetInteger(IL_IMAGE_WIDTH);
		Height = ilGetInteger(IL_IMAGE_HEIGHT);
		Type = ilGetInteger(IL_IMAGE_TYPE); // matches OpenGL
		Format = ilGetInteger(IL_IMAGE_FORMAT); // matches OpenGL
	}
	else
	{
		error = ilGetError();
		return false;
	}
	return true;
}

ILubyte* VImage::GetData()
{
	return Data;
}

int VImage::GetWidth()
{
	return Width;
}

int VImage::GetHeight()
{
	return Height;
}

int VImage::GetType()
{
	return Type;
}

int VImage::GetFormat()
{
	return Format;
}


VImage::~VImage()
{
	ilDeleteImages(1, &imageID);
}
