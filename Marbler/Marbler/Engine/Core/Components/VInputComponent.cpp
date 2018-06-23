#include "VInputComponent.h"

#include "../VInputManager.h"
#include "../Objects/VActor.h"
#include "VCameraComponent.h"
#include "PxRigidActor.h"
#include "../../Utils/PhysxUtils.h"
#include "../VGameStatics.h"
#include "../VGame.h"

#include <iostream>
#include <glm/gtx/rotate_vector.hpp>


VInputComponent::VInputComponent(VScene* Scene, std::string Name) : VActorComponent(Scene, Name)
{
	this->Scene = Scene;
}

void VInputComponent::OnInitialize()
{
	VInputManager::BindAction("Forward", KEY_W, VActionType::Pressed, *this, &VInputComponent::OnForwardPressed);
	VInputManager::BindAction("Back", KEY_S, VActionType::Pressed, *this, &VInputComponent::OnBackwardPressed);
	VInputManager::BindAction("Left", KEY_A, VActionType::Pressed, *this, &VInputComponent::OnLeftPressed);
	VInputManager::BindAction("Right", KEY_D, VActionType::Pressed, *this, &VInputComponent::OnRightPressed);
	VInputManager::BindAction("Up", KEY_SPACE, VActionType::Pressed, *this, &VInputComponent::OnUpPressed);
	VInputManager::BindAction("Down", KEY_LEFT_SHIFT, VActionType::Pressed, *this, &VInputComponent::OnDownPressed);
	VInputManager::BindAction("Forward", KEY_W, VActionType::Released, *this, &VInputComponent::OnForwardReleased);
	VInputManager::BindAction("Back", KEY_S, VActionType::Released, *this, &VInputComponent::OnBackwardReleased);
	VInputManager::BindAction("Left", KEY_A, VActionType::Released, *this, &VInputComponent::OnLeftReleased);
	VInputManager::BindAction("Right", KEY_D, VActionType::Released, *this, &VInputComponent::OnRightReleased);
	VInputManager::BindAction("Up", KEY_SPACE, VActionType::Released, *this, &VInputComponent::OnUpReleased);
	VInputManager::BindAction("Down", KEY_LEFT_SHIFT, VActionType::Released, *this, &VInputComponent::OnDownReleased);
	VInputManager::BindAction("Space", KEY_SPACE, VActionType::Pressed, *this, &VInputComponent::OnSpaceBarPressed);
	VInputManager::BindAction("M", KEY_M, VActionType::Pressed, *this, &VInputComponent::OnMPressed);
	VInputManager::BindAction("F1", KEY_F1, VActionType::Pressed, *this, &VInputComponent::OnF1Pressed);
	VInputManager::BindAction("F2", KEY_F2, VActionType::Pressed, *this, &VInputComponent::OnF2Pressed);
	VInputManager::BindAction("F3", KEY_F3, VActionType::Pressed, *this, &VInputComponent::OnF3Pressed);
	VInputManager::BindAction("F4", KEY_F4, VActionType::Pressed, *this, &VInputComponent::OnF4Pressed);
	VInputManager::BindAction("F8", KEY_F8, VActionType::Pressed, *this, &VInputComponent::OnF8Pressed);

	VInputManager::BindAction("Quit", KEY_ESC, VActionType::Pressed, *this, &VInputComponent::OnQuitPressed);

	VInputManager::BindMouse(*this, &VInputComponent::OnMouseMoved);
}

void VInputComponent::Update(double deltaT)
{
	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);

	if (InputMode)
	{
		VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();
		glm::vec3 CameraForward = CameraComponent->GetForward();
		CameraForward.y = 0;
		CameraForward = glm::normalize(CameraForward);
		CameraForward = glm::rotateY(CameraForward, glm::radians<float>(90.0));
		//CameraForward.x = CameraForward.x * MovementVector.x;
		//CameraForward.y = CameraForward.y * MovementVector.y;
		CameraForward.x = CameraForward.x * -MovementVector.x;
		CameraForward.z = CameraForward.z * -MovementVector.x;
		//CameraForward.y = 0;
		//CameraForward.z = 0;

		((PxRigidDynamic*)ActorOwner->GetRigidActor())->addTorque(PhysxUtils::ConvertGVec3ToPxVec3(CameraForward*MovementSpeed));
	}
	else
	{
		((PxRigidDynamic*)ActorOwner->GetRigidActor())->addTorque(PhysxUtils::ConvertGVec3ToPxVec3(MovementVector*MovementSpeed));
	}


	//std::cout << "X: " << CameraForward.x << " Y: " << CameraForward.y << " Z: " << CameraForward.z << std::endl;
	
}

void VInputComponent::OnForwardPressed()
{

	MovementVector += glm::vec3(-1.0f, 0.0f, 0.0f);
}

void VInputComponent::OnBackwardPressed()
{
	MovementVector += glm::vec3(1.0f, 0.0f, 0.0f);
}

void VInputComponent::OnLeftPressed()
{
	MovementVector += glm::vec3(0.0f, 0.0f , 1.0f);
}

void VInputComponent::OnRightPressed()
{
	MovementVector += glm::vec3(0.0f, 0.0f, -1.0f);
}

void VInputComponent::OnUpPressed()
{
}

void VInputComponent::OnDownPressed()
{
}

void VInputComponent::OnForwardReleased()
{
	MovementVector += glm::vec3(1.0f, 0.0f, 0.0f);
}

void VInputComponent::OnBackwardReleased()
{
	MovementVector += glm::vec3(-1.0f, 0.0f, 0.0f);
}

void VInputComponent::OnLeftReleased()
{
	MovementVector += glm::vec3(0.0f, 0.0f, -1.0f);
}

void VInputComponent::OnRightReleased()
{
	MovementVector += glm::vec3(0.0f, 0.0f, 1.0f);
}

void VInputComponent::OnUpReleased()
{
}

void VInputComponent::OnDownReleased()
{
}

void VInputComponent::OnSpaceBarPressed()
{
	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);
	((PxRigidDynamic*)ActorOwner->GetRigidActor())->addForce(PhysxUtils::ConvertGVec3ToPxVec3(glm::vec3(0.0f, 1.0f, 0.0f)*JumpForce));
}

void VInputComponent::OnMPressed()
{
	this->ChangeInputMode(!InputMode);
}

void VInputComponent::OnF1Pressed()
{
	VGameStatics::GetGame()->OnHelpDelegate();
}

void VInputComponent::OnF2Pressed()
{
	VGameStatics::GetGame()->OnFPSDelegate();
}

void VInputComponent::OnF3Pressed()
{
	VGameStatics::GetGame()->OnWireFrameDelegate();
}

void VInputComponent::OnF4Pressed()
{
	VGameStatics::GetGame()->OnRecompileDelegate();
}

void VInputComponent::OnF8Pressed()
{
	VGameStatics::GetGame()->OnFrustumDelegate();
}


void VInputComponent::OnQuitPressed()
{
	VGameStatics::GetGame()->QuitGame();
}

void VInputComponent::ChangeInputMode(bool InputMode)
{
	this->InputMode = InputMode;
}

void VInputComponent::SetJumpForce(float JumpForce)
{
	this->JumpForce = JumpForce;
}

void VInputComponent::SetMovementSpeed(float MovementSpeed)
{
	this->MovementSpeed = MovementSpeed;
}

void VInputComponent::SetMaxSpeed(float MaxSpeed)
{
	this->MaxSpeed = MaxSpeed;

	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);

	((PxRigidDynamic*)ActorOwner->GetRigidActor())->setMaxAngularVelocity(this->MaxSpeed);
}

void VInputComponent::OnMouseMoved(double deltaX, double deltaY)
{
	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);

	VCameraComponent* Camera = ActorOwner->GetComponentByClass<VCameraComponent>();
	Camera->IncreaseTheta(deltaX*0.01f);
	Camera->IncreasePhi(deltaY*0.01f);
}

VInputComponent::~VInputComponent()
{
}
