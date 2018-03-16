#include "VDirectionalLight.h"

VDirectionalLight::VDirectionalLight() : VMesh()
{

}

float VDirectionalLight::GetAmbient()
{
	return Ambient;
}

glm::vec3 VDirectionalLight::GetColor()
{
	return Color;
}

float VDirectionalLight::GetDiffuse()
{
	return Diffuse;
}

void VDirectionalLight::SetAmbient(float Ambient)
{
	this->Ambient = Ambient;
}

void VDirectionalLight::SetColor(glm::vec3 Color)
{
	this->Color = Color;
}

void VDirectionalLight::SetDiffuse(float Diffuse)
{
	this->Diffuse = Diffuse;
}

void VDirectionalLight::SetDirection(glm::vec3 Direction)
{
	this->Direction = Direction;
}

void VDirectionalLight::Draw(glm::mat4 ParentModelMatrix)
{
	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

VDirectionalLight::~VDirectionalLight()
{

}