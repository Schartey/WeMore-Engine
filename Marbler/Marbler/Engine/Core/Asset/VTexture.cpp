#include "VTexture.h"



VTexture::VTexture()
{
}

int VTexture::GetId()
{
	return Id;
}

GLuint VTexture::LoadTextureFromFile(std::string name) {

	FILE *fp;
	errno_t err;
							  /* try to open the file */
	err = fopen_s(&fp, name.c_str(), "rb");
	if (err != 0) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", name.c_str()); getchar();
		return -1;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	this->Id = this->LoadImage(name.c_str());
	fclose(fp);
}

GLuint VTexture::LoadImage(const char* path)
{
	ILuint imageID;				// Create an image ID as a ULuint

	GLuint textureID;			// Create a texture ID as a GLuint

	bool success;			// Create a flag to keep track of success/failure

	ILenum error;				// Create a flag to keep track of the IL error state

	ilGenImages(1, &imageID); 		// Generate the image ID
	ilBindImage(imageID); 			// Bind the image

	success = ilLoadImage(path); 	// Load the image file

									// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		ILubyte* data = ilGetData();
		if (!data) {
			ilBindImage(0);
			ilDeleteImages(1, &imageID);
			return 0;
		}

		int const width = ilGetInteger(IL_IMAGE_WIDTH);
		int const height = ilGetInteger(IL_IMAGE_HEIGHT);
		int const type = ilGetInteger(IL_IMAGE_TYPE); // matches OpenGL
		int const format = ilGetInteger(IL_IMAGE_FORMAT); // matches OpenGL

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		/*glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // rows are tightly packed
		glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
		glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // pixels are tightly packed*/

		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else // If we failed to open the image file in the first place...
	{
		error = ilGetError();
		exit(-1);
	}

	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

	return textureID; // Return the GLuint to the texture so you can use it!
}

VTexture::~VTexture()
{
}
