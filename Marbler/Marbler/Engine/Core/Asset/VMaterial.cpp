#include "VMaterial.h"

#include <glm/gtc/type_ptr.hpp>

VMaterial::VMaterial()
{
	Shader = new VShader("Engine/Shader/base.vert", "Engine/Shader/base.frag");
}

VShader* VMaterial::GetShader()
{
	return Shader;
}

void VMaterial::SetShader(VShader* Shader) 
{
	this->Shader = Shader;
}

void VMaterial::Use()
{
	Shader->useShader();
}

void VMaterial::ApplyInformation()
{
	int texturesInUse = 0;

	glUniform1i(glGetUniformLocation(Shader->programHandle, "diffuseTextureSize"), this->DiffuseTextures.size());
	glUniform1i(glGetUniformLocation(Shader->programHandle, "lightmapTextureSize"), this->LightMapTextures.size());

	for (int i = 0; i < DiffuseTextures.size() && DiffuseTextures.size() < 10; i++)
	{
		glActiveTexture(GL_TEXTURE0 + texturesInUse);
		glBindTexture(GL_TEXTURE_2D, this->DiffuseTextures[i]->GetId());

		GLuint uUniform = glGetUniformLocation(Shader->programHandle, ("diffuseTexture[" + std::to_string(i) + "]").c_str());
		glUniform1i(uUniform, texturesInUse);

		texturesInUse++;
	}

	for (int i = 0; i < LightMapTextures.size() && LightMapTextures.size() < 10; i++)
	{
		glActiveTexture(GL_TEXTURE0 + texturesInUse);
		glBindTexture(GL_TEXTURE_2D, this->LightMapTextures[i]->GetId());

		GLuint uUniform = glGetUniformLocation(Shader->programHandle, ("lightmapTexture[" + std::to_string(i) + "]").c_str());
		glUniform1i(uUniform, texturesInUse);

		texturesInUse++;
	}

	glUniform3fv(glGetUniformLocation(Shader->programHandle, "material.ambient"), 1, glm::value_ptr(Ambient));
	glUniform3fv(glGetUniformLocation(Shader->programHandle, "material.diffuse"), 1, glm::value_ptr(Diffuse));
	glUniform3fv(glGetUniformLocation(Shader->programHandle, "material.specular"), 1, glm::value_ptr(Specular));
	glUniform1f(glGetUniformLocation(Shader->programHandle, "material.shininess"), Shininess);
}

void VMaterial::Release()
{

}

void VMaterial::SetAmbient(glm::vec3 Ambient)
{
	this->Ambient = Ambient;
}

void VMaterial::SetDiffuse(glm::vec3 Diffuse)
{
	this->Diffuse = Diffuse;
}

void VMaterial::SetSpecular(glm::vec3 Specular)
{
	this->Specular = Specular;
}

void VMaterial::SetShininess(float Shininess)
{
	this->Shininess = Shininess;
}

void VMaterial::AddDiffuseTexture(VTexture* Texture)
{
	DiffuseTextures.push_back(Texture);
}

void VMaterial::AddLightMapTexture(VTexture* Texture)
{
	LightMapTextures.push_back(Texture);
}

VMaterial::~VMaterial()
{
}
