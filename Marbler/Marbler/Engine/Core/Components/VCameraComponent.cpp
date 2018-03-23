#include "VCameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../Objects/VActor.h"

#include <iostream>

VCameraComponent::VCameraComponent(VScene* Scene, std::string Name) : VSceneComponent(Scene, Name)
{

}

glm::mat4 VCameraComponent::Orientation() const {
	glm::mat4 orientation;
	orientation = glm::rotate(orientation, glm::radians(Phi), glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, glm::radians(Theta), glm::vec3(0, 1, 0));
	return orientation;
}

glm::vec3 VCameraComponent::Forward() const {
	glm::vec4 forward = glm::inverse(Orientation()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}

glm::vec3 VCameraComponent::Right() const {
	glm::vec4 right = glm::inverse(Orientation()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}

glm::vec3 VCameraComponent::Up() const {
	glm::vec4 up = glm::inverse(Orientation()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
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
	//ViewMatrix = glm::rotate(ViewMatrix, Theta, Right());
	this->Theta += Theta;
	std::cout << "Y: " << Theta << '\n';
}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	if (bHasTarget)
	{
		glm::quat QuatYaw = glm::angleAxis(Theta, glm::vec3(0, 1, 0));
		glm::vec3 Direction = glm::normalize(GetGlobalPosition() - Target->GetGlobalPosition());
		glm::quat QuatPitch = glm::angleAxis(Phi, glm::cross(Direction, glm::vec3(0, 1, 0)));
		glm::mat4 CombinedMat = glm::toMat4(QuatYaw * QuatPitch);
		glm::vec4 newPosition = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 5.0f)) * CombinedMat*glm::vec4(Target->GetGlobalPosition(), 1.0f);

		//pitch
		//glm::vec3 newPosition = glm::rotate(Theta, Right()) * glm::vec4((GetGlobalPosition() - Target->GetGlobalPosition()) + Target->GetGlobalPosition(), 0.0);
		//newPosition = (glm::rotate(Phi, glm::vec3(0,1,0)) * glm::vec4((newPosition) + Target->GetGlobalPosition(), 0.0));


		//yaw, Y-up system
		//position = (Rotate(some other angle, (0, 1, 0)) * (position - target)) + target;

		//glm::vec3 direction = normalize(Target->GetGlobalPosition() - GetGlobalPosition());
		//glm::vec3 newDirection = glm::rotate(direction, Phi, glm::vec3(0.0f, 1.0f, 0.0f));
		//newDirection = glm::rotate(newDirection, Theta, glm::vec3(1.0f, 0.0f, 0.0f));
		//glm::vec3 newPos = Target->GetGlobalPosition() + newDirection * 10.0f;

		//glm::vec3 newPos = Target->GetGlobalPosition();
		//glm::vec3 newDirection = glm::normalize(glm::rotateX(newPos, 10.0f));
		
		//newPos += newPos + (newDirection * 10.0f);

		//float eyeX = Target->GetGlobalPosition().x + Radius * cos(Phi)*sin(Theta);
		//float eyeY = Target->GetGlobalPosition().y + Radius * sin(Phi)*sin(Theta);
		//float eyeZ = Target->GetGlobalPosition().z + Radius * cos(Theta);

		//Position = newPos;
		ViewMatrix = glm::lookAt(glm::vec3(newPosition),
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

	ViewMatrix = glm::lookAt(GetGlobalPosition(),
		Target->GetGlobalPosition(),
		glm::vec3(0.0f, 1.0f, 0.0f));

	this->bHasTarget = true;
}

void VCameraComponent::SetProjectionMatrix(glm::mat4 ProjectionMatrix)
{
	this->ProjectionMatrix = ProjectionMatrix;
}

VCameraComponent::~VCameraComponent()
{

}