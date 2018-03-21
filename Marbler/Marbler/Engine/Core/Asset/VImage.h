#pragma once

#include <string>
#include "GL/glew.h"

#include "IL/il.h"

class VImage
{
public:
	VImage(std::string fileName);
	
	bool Load();

	ILubyte* GetData();
	int GetWidth();
	int GetHeight();
	int GetType();
	int GetFormat();

	~VImage();

private:
	std::string fileName;

	ILuint imageID;				// Create an image ID as a ULuint
	ILubyte* Data;
	int Width;
	int Height;
	int Type;
	int Format;


};

