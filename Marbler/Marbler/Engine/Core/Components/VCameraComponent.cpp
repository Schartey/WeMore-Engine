#include "VCameraComponent.h"

#include "glm/gtc/matrix_transform.hpp"
#include "../VActor.h"

VCameraComponent::VCameraComponent()
{

}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 VCameraComponent::GetProjectionMatrix()
{
	return ProjectionMatrix;
}

void VCameraComponent::SetLookAt(glm::vec3 LookAtVector)
{
	ModelMatrix = Owner->GetModelMatrix()*TranslationMatrix * RotationMatrix*ScaleMatrix;
	ViewMatrix = glm::lookAt(glm::vec3(ModelMatrix[3]), LookAtVector, glm::vec3(0, 1, 0));
}

void VCameraComponent::SetProjectionMatrix(glm::mat4 ProjectionMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
}

VCameraComponent::~VCameraComponent()
{

}