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

glm::vec3 VDirectionalLight::GetDirection()
{
	return Direction;
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

void VDirectionalLight::Draw()
{
	VMesh::Draw();
}

VDirectionalLight::~VDirectionalLight()
{

}