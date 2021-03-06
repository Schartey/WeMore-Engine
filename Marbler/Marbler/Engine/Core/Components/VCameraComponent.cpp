#include "VCameraComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "../Objects/VActor.h"

#include <iostream>

VCameraComponent::VCameraComponent(VScene* Scene, std::string Name) : VSceneComponent(Scene, Name)
{
	Frustum = new VFrustum();
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
	LastCameraInteractionTime = 0.0f;
	if (this->Phi + Phi > -1.8 && this->Phi + Phi < 1.28)
	{
		this->Phi += Phi;
	}
}

void VCameraComponent::IncreaseTheta(float Theta)
{
	LastCameraInteractionTime = 0.0f;
	this->Theta += Theta;
}

glm::vec3 VCameraComponent::GetForward()
{
	glm::vec3 Position = GetModel()*glm::vec4(1.0f);

	return glm::normalize(Target->GetGlobalPosition() - Position);
}

glm::mat4 VCameraComponent::GetViewMatrix()
{
	if (bHasTarget)
	{

		/*if (LastCameraInteractionTime > CameraSwitchTime)
		{
		glm::quat MarbleDirection = Target->GetGlobalRotation();
		glm::vec3 ShouldBePosition = Target->GetGlobalPosition() - glm::vec3(glm::toMat4(MarbleDirection)*glm::vec4(1.0f));

		glm::vec3 Distance = ShouldBePosition - Position;
		glm::vec3 BlendDistance = glm::normalize(Distance);
		BlendDistance *= (BlendSpeed*deltaT);
		NewPosition = Position + BlendDistance;;
		}*/
		glm::quat QuatYaw = glm::angleAxis(Theta, glm::vec3(0, 1, 0));
		glm::mat4 Translation = glm::translate(glm::mat4(), GetPosition());

		glm::vec3 PositionAfterYaw = glm::toMat4(QuatYaw) * Translation * glm::vec4(1.0f);

		//We need position after yaw but projected on a flat circle so we just put it on the circle
		PositionAfterYaw.y = 0;
		//Get the direction now from the center point and normalize it
		glm::vec3 Direction = normalize(PositionAfterYaw - glm::vec3(0));
		//Get the Orthogonal - Vektor of Direction to up (0,1,0), we want to rotate around this vektor
		glm::vec3 quatDirection = glm::cross(Direction, glm::vec3(0, 1, 0));
		glm::quat QuatPitch = glm::angleAxis(Phi, quatDirection);

		//((VActor*)Owner)->GetMovementVector();
		//glm::quat QuatParent;// = glm::angleAxis(glm::cross(Owner->GetMovementVector(), glm::vec3(0, 1, 0)), glm::vec3(0, 1, 0));

		glm::vec3 thePosition = glm::toMat4(QuatPitch*QuatYaw) * Translation * glm::vec4(1.0f);
		thePosition += Target->GetGlobalPosition();

		Model = glm::translate(glm::mat4(), thePosition);

		Frustum->setCamDef(thePosition, Target->GetGlobalPosition(), glm::vec3(0, 1, 0));

		ViewMatrix = glm::lookAt(thePosition,
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

VFrustum* VCameraComponent::GetFrustum()
{
	return Frustum;
}

void VCameraComponent::SetTarget(VSceneComponent* SceneComponent)
{
	this->Target = SceneComponent;

	/*ViewMatrix = glm::lookAt(GetGlobalPosition(),
		Target->GetGlobalPosition(),
		glm::vec3(0.0f, 1.0f, 0.0f));*/

	this->bHasTarget = true;
}

void VCameraComponent::SetProjectionMatrix(float Fov, int Width, int Height, float NearPlane, float FarPlane)
{
	this->Fov = Fov;
	this->NearPlane = NearPlane;
	this->FarPlane = FarPlane;
	this->Ratio = Width / (float)Height;
	this->HeightNear = 2 * glm::tan(Fov / 2)*NearPlane;
	this->WidthNear = HeightNear * this->Ratio;
	this->HeightFar = 2 * glm::tan(Fov / 2)*FarPlane;
	this->WidthFar = HeightFar * this->Ratio;


	Frustum->setCamInternals(Fov, this->Ratio, NearPlane, FarPlane);

	this->ProjectionMatrix = glm::perspective(glm::radians(Fov), Width / (float)Height, NearPlane, FarPlane);
}


void VCameraComponent::Update(double deltaT)
{
	VSceneComponent::Update(deltaT);
	LastCameraInteractionTime += deltaT;
}
VCameraComponent::~VCameraComponent()
{

}