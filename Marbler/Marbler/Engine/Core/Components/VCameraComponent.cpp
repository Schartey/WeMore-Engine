#include "VCameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "../VActor.h"

VCameraComponent::VCameraComponent(VScene* Scene) : VSceneComponent(Scene)
{

}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	ModelMatrix = translate(glm::mat4(), this->Position)*glm::toMat4(this->Rotation)*glm::scale(glm::mat4(), this->Scale), Owner->GetScale();
	ViewMatrix = Owner->GetModelMatrix()*ModelMatrix;
	return ViewMatrix;
}

glm::mat4 VCameraComponent::GetProjectionMatrix()
{
	return ProjectionMatrix;
}

void VCameraComponent::SetProjectionMatrix(glm::mat4 ProjectionMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
}

VCameraComponent::~VCameraComponent()
{

}