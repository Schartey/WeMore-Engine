#pragma once


class VTexture
{
public:
	VTexture();

	//void LoadTextureFromFile(const char* name, std::string directory);

	int GetId();

	~VTexture();

private:
	int Id;

	//int LoadDDS(FILE* FFile);
};

