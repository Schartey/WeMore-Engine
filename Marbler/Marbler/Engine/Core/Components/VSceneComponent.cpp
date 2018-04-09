#include "VSceneComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../Objects/VSceneObject.h"

VSceneComponent::VSceneComponent(VScene* Scene, std::string Name) : VActorComponent(Scene, Name)
{
}

glm::mat4 VSceneComponent::GetGlobalModelMatrix()
{
	return translate(glm::mat4(), this->Position + Owner->GetPosition())*glm::toMat4(this->Rotation)*glm::scale(glm::mat4(), this->Scale * Owner->GetScale());
}

glm::mat4 VSceneComponent::GetModelMatrix()
{
	return ModelMatrix;
}

glm::vec3 VSceneComponent::GetPosition()
{
	return this->Position;
}
glm::vec3 VSceneComponent::GetGlobalPosition()
{
	return this->Position + this->Owner->GetPosition();
}

glm::quat VSceneComponent::GetGlobalRotation()
{
	return this->Rotation * this->Owner->GetRotation();
}

void VSceneComponent::SetPosition(glm::vec3 Position)
{
	this->Position = Position;
}

void VSceneComponent::SetRotation(glm::vec3 Rotation)
{
	this->Rotation = glm::quat(Rotation);
}

void VSceneComponent::SetRotation(glm::quat Rotation)
{
	this->Rotation = Rotation;
}

void VSceneComponent::SetScale(glm::vec3 Scale)
{
	this->Scale = Scale;
}

void VSceneComponent::Update(double deltaT)
{
	ModelMatrix = translate(glm::mat4(), this->Position)*glm::toMat4(this->Rotation)*glm::scale(glm::mat4(), this->Scale);
}
void VSceneComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix)
{

}

void VSceneComponent::Draw(glm::mat4 ParentModelMatrix)
{

}


VSceneComponent::~VSceneComponent()
{
}
