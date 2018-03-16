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
	void ApplyInformation();
	void Release();

	void SetAmbient(glm::vec3 Ambient);
	void SetDiffuse(glm::vec3 Diffuse);
	void SetSpecular(glm::vec3 Specular);
	void SetShininess(float Shininess);

	void AddDiffuseTexture(VTexture* Texture);
	void AddLightMapTexture(VTexture* Texture);

	~VMaterial();

private:
	VShader* Shader;

	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular;
	float Shininess;

	std::vector<VTexture*> DiffuseTextures;
	std::vector<VTexture*> LightMapTextures;
};

