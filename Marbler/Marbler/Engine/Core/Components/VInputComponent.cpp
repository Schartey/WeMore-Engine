#include "VInputComponent.h"

#include "../VInputManager.h"
#include "../VActor.h"
#include "VCameraComponent.h"


VInputComponent::VInputComponent(VScene* Scene) : VActorComponent(Scene)
{
}

void VInputComponent::OnInitialize()
{
	VInputManager::BindAction("Forward", KEY_W, VActionType::Pressed, *this, &VInputComponent::OnForward);
	VInputManager::BindAction("Back", KEY_S, VActionType::Pressed, *this, &VInputComponent::OnBackward);
	VInputManager::BindAction("Left", KEY_A, VActionType::Pressed, *this, &VInputComponent::OnLeft);
	VInputManager::BindAction("Right", KEY_D, VActionType::Pressed, *this, &VInputComponent::OnRight);
	VInputManager::BindAction("Up", KEY_SPACE, VActionType::Pressed, *this, &VInputComponent::OnUp);
	VInputManager::BindAction("Down", KEY_LEFT_SHIFT, VActionType::Pressed, *this, &VInputComponent::OnDown);
}

void VInputComponent::OnForward()
{
	Owner->SetPosition(Owner->GetPosition()+glm::vec3(0.0f, -0.0f, 0.5f));
}

void VInputComponent::OnBackward()
{
	Owner->SetPosition(Owner->GetPosition() + glm::vec3(0.0f, 0.0f, -0.5f));
}

void VInputComponent::OnLeft()
{
	Owner->SetPosition(Owner->GetPosition() + glm::vec3(0.5f, 0.0f, 0.0f));
}

void VInputComponent::OnRight()
{
	Owner->SetPosition(Owner->GetPosition() + glm::vec3(-0.5f, 0.0f, 0.0f));
}

void VInputComponent::OnUp()
{
	Owner->SetPosition(Owner->GetPosition() + glm::vec3(0.0f, -0.5f, 0.0f));
}

void VInputComponent::OnDown()
{
	Owner->SetPosition(Owner->GetPosition() + glm::vec3(0.0f, 0.5f, 0.0f));
}

VInputComponent::~VInputComponent()
{
}
