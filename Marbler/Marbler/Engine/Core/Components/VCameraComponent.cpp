#include "VCameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "../VActor.h"

VCameraComponent::VCameraComponent()
{

}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	ViewMatrix = Owner->GetModelMatrix()*TranslationMatrix * RotationMatrix*ScaleMatrix;
	return ViewMatrix;
}

void VCameraComponent::Rotate(glm::vec3 Rotate)
{
	//FPS camera:  RotationX(pitch) * RotationY(yaw)
	glm::quat qPitch = glm::angleAxis(Rotate.y, glm::vec3(1, 0, 0));
	glm::quat qYaw = glm::angleAxis(Rotate.x, glm::vec3(0, 1, 0));
	glm::quat qRoll = glm::angleAxis(Rotate.z, glm::vec3(0, 0, 1));

	//For a FPS camera we can omit roll
	glm::quat orientation = qPitch * qYaw;
	orientation = glm::normalize(orientation);
	RotationMatrix = glm::mat4_cast(orientation);

}

glm::mat4 VCameraComponent::GetProjectionMatrix()
{
	return ProjectionMatrix;
}

void VCameraComponent::SetLookAt(glm::vec3 LookAtVector)
{
	this->LookAt = LookAtVector;
	glm::mat4 CModelMatrix = Owner->GetModelMatrix()*TranslationMatrix * RotationMatrix*ScaleMatrix;
	glm::vec3 camPos = CModelMatrix[3];
	ViewMatrix = glm::lookAt(camPos, LookAtVector, glm::vec3(0, 1, 0));
}

void VCameraComponent::SetProjectionMatrix(glm::mat4 ProjectionMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
}

void VCameraComponent::UpdateViewMatrix()
{
	ViewMatrix = Owner->GetModelMatrix()*TranslationMatrix * RotationMatrix*ScaleMatrix;
}

VCameraComponent::~VCameraComponent()
{

}