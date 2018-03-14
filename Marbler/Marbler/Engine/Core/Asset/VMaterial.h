#pragma once

#include <vector>

#include "../VShader.h"
#include "VTexture.h"

class VMaterial
{
public:
	VMaterial();

	VShader* GetShader();
	void SetShader(VShader* Shader);

	void Use();
	void Release();

	void AddDiffuseTexture(VTexture* Texture);
	void AddLightMapTexture(VTexture* Texture);

	~VMaterial();

private:
	VShader* Shader;

	std::vector<VTexture*> DiffuseTextures;
	std::vector<VTexture*> LightMapTextures;
};

