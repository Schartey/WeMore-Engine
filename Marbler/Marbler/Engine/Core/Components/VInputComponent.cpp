#include "VInputComponent.h"

#include "../VInputManager.h"
#include "../Objects/VActor.h"
#include "VCameraComponent.h"
#include "PxRigidActor.h"
#include "../../Utils/PhysxUtils.h"
#include "../VGameStatics.h"
#include "../VGame.h"

#include <iostream>


VInputComponent::VInputComponent(VScene* Scene, std::string Name) : VActorComponent(Scene, Name)
{
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

	VInputManager::BindAction("Quit", KEY_ESC, VActionType::Pressed, *this, &VInputComponent::OnQuitPressed);

	VInputManager::BindMouse(*this, &VInputComponent::OnMouseMoved);
}

void VInputComponent::Update(double deltaT)
{
	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);

	((PxRigidDynamic*)ActorOwner->GetRigidActor())->addTorque(PhysxUtils::ConvertGVec3ToPxVec3(MovementVector*MovementSpeed));
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

void VInputComponent::OnQuitPressed()
{
	VGameStatics::GetGame()->QuitGame();
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
