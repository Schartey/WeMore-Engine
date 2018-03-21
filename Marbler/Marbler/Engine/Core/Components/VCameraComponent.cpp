#include "VCameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include "../Objects/VActor.h"

VCameraComponent::VCameraComponent(VScene* Scene) : VSceneComponent(Scene)
{

}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	if (bHasTarget)
	{

	}
	else
	{
		glm::vec3 VPosition = (this->Position+Owner->GetPosition());
		glm::vec3 cameraDirection = Rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 cameraTarget = VPosition - cameraDirection;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		ViewMatrix = glm::lookAt(VPosition,
			cameraTarget,
			glm::vec3(0.0f, 1.0f, 0.0f));
		//ViewMatrix = glm::lookAt(VPosition, forwardTarget, upTarget);
		//ModelMatrix = translate(glm::mat4(), (this->Position+this->Owner->GetPosition()))*glm::toMat4(this->Rotation);
		//ViewMatrix = Owner->GetModelMatrix()*ModelMatrix;
	}
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