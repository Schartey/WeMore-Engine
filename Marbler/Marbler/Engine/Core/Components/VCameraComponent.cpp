#include "VCameraComponent.h"

VCameraComponent::VCameraComponent()
{

}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	return TranslationMatrix;
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