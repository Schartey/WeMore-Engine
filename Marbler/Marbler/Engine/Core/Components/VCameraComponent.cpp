#include "VCameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../Objects/VActor.h"

#include <iostream>

VCameraComponent::VCameraComponent(VScene* Scene, std::string Name) : VSceneComponent(Scene, Name)
{

}

float VCameraComponent::GetPhi()
{
	return Phi;
}

float VCameraComponent::GetTheta()
{
	return Theta;
}

void VCameraComponent::IncreasePhi(float Phi)
{
	this->Phi += Phi;
	std::cout << "X: " << Phi << '\n';
}

void VCameraComponent::IncreaseTheta(float Theta)
{
	this->Theta += Theta;
	std::cout << "Y: " << Theta << '\n';
}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	if (bHasTarget)
	{
		glm::vec3 direction = normalize(Target->GetGlobalPosition() - GetGlobalPosition());
		glm::vec3 newDirection = glm::rotate(direction, Phi, glm::vec3(0.0f, 1.0f, 0.0f));
		//newDirection = glm::rotate(newDirection, Theta, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::vec3 newPos = Target->GetGlobalPosition() + newDirection * 10.0f;

		//glm::vec3 newPos = Target->GetGlobalPosition();
		//glm::vec3 newDirection = glm::normalize(glm::rotateX(newPos, 10.0f));
		
		//newPos += newPos + (newDirection * 10.0f);

		//float eyeX = Target->GetGlobalPosition().x + Radius * cos(Phi)*sin(Theta);
		//float eyeY = Target->GetGlobalPosition().y + Radius * sin(Phi)*sin(Theta);
		//float eyeZ = Target->GetGlobalPosition().z + Radius * cos(Theta);

		//Position = newPos;
		ViewMatrix = glm::lookAt(newPos,
			Target->GetGlobalPosition(),
			glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else
	{
		glm::vec3 VPosition = GetGlobalPosition();
		glm::vec3 cameraDirection = Rotation * glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 cameraTarget = VPosition - cameraDirection;
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		ViewMatrix = glm::lookAt(VPosition,
			cameraTarget,
			glm::vec3(0.0f, 1.0f, 0.0f));
	}
	return ViewMatrix;
}

glm::mat4 VCameraComponent::GetProjectionMatrix()
{
	return ProjectionMatrix;
}

void VCameraComponent::SetTarget(VSceneComponent* SceneComponent)
{
	this->Target = SceneComponent;
	this->bHasTarget = true;
}

void VCameraComponent::SetProjectionMatrix(glm::mat4 ProjectionMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
}

VCameraComponent::~VCameraComponent()
{

}