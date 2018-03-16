#include "VPointLight.h"

#include "../../Utils/Assimp/VAssimpUtils.h"


VPointLight::VPointLight() : VMesh()
{
}

void VPointLight::SetAmbient(float Ambient)
{
	this->Ambient = Ambient;
}

void VPointLight::SetColor(glm::vec3 Color)
{
	this->Color = Color;
}

void VPointLight::SetDiffuse(float Diffuse)
{
	this->Diffuse = Diffuse;
}

void VPointLight::SetAttenuation(VAttenuation Attenuation)
{
	this->Attenuation = Attenuation;
}

float VPointLight::GetAmbient()
{
	return Ambient;
}

glm::vec3 VPointLight::GetColor()
{
	return Color;
}

float VPointLight::GetDiffuse()
{
	return Diffuse;
}

VAttenuation VPointLight::GetAttenuation()
{
	return Attenuation;
}

void VPointLight::Draw(glm::mat4 ParentModelMatrix)
{
	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

VPointLight::~VPointLight()
{

}