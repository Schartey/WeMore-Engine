#include "VInputComponent.h"

#include "../VInputManager.h"
#include "../VActor.h"


VInputComponent::VInputComponent()
{
}

void VInputComponent::OnInitialize()
{
	VInputManager::BindAction("Forward", KEY_W, VActionType::Pressed, *this, &VInputComponent::OnForward);
}

void VInputComponent::OnForward()
{
	Owner->Translate(glm::vec3(0.0f, -0.5f, 0.0f));
}


VInputComponent::~VInputComponent()
{
}
