#include "VSceneComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

VSceneComponent::VSceneComponent(VScene* Scene) : VActorComponent(Scene)
{
}

glm::mat4 VSceneComponent::GetModelMatrix()
{
	return ModelMatrix;
}

glm::vec3 VSceneComponent::GetPosition()
{
	return this->Position;
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

void VSceneComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix)
{

}

void VSceneComponent::Draw(glm::mat4 ParentModelMatrix)
{

}


VSceneComponent::~VSceneComponent()
{
}
