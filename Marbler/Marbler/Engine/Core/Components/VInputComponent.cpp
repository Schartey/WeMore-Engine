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
	VInputManager::BindAction("Turn", KEY_D, VActionType::Pressed, *this, &VInputComponent::Turn);
}

void VInputComponent::OnForward()
{
	Owner->SetPosition(Owner->GetPosition()+glm::vec3(0.0f, -0.5f, 0.0f));
}

void VInputComponent::Turn()
{
	//Owner->GetComponentByClass<VCameraComponent>()->Rotate(glm::vec3(0.0f, 1.0f, 0.0f));
}


VInputComponent::~VInputComponent()
{
}
