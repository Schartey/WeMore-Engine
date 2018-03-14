#include "VMaterial.h"



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

void VMaterial::Release()
{

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
