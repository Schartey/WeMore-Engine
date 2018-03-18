#pragma once

#include <vector>

#include "glm/glm.hpp"

#include "../VShader.h"
#include "VTexture.h"

class VMaterial
{
public:
	VMaterial();

	VShader* GetShader();
	void SetShader(VShader* Shader);

	void Use();
	void ApplyRenderPassInformation(VShader* Shader);
	void ApplyInformation();
	void Release();

	void SetAmbient(float Ambient);
	void SetDiffuse(glm::vec3 Diffuse);
	void SetSpecularColor(glm::vec3 SpecularColor);
	void SetSpecularIntensity(float SpecularIntensity);
	void SetSpecularPower(float SpecularPower);

	void AddDiffuseTexture(VTexture* Texture);
	void AddLightMapTexture(VTexture* Texture);

	~VMaterial();

private:
	VShader* Shader;

	float Ambient;
	glm::vec3 Diffuse;
	glm::vec3 SpecularColor;
	float SpecularIntensity;
	float SpecularPower;

	std::vector<VTexture*> DiffuseTextures;
	std::vector<VTexture*> LightMapTextures;
};

