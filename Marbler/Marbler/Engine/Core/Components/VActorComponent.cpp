#include "VActorComponent.h"

#include "../Objects/VActor.h"

VActorComponent::VActorComponent(VScene* Scene, std::string Name)
{
	this->Scene = Scene;
	this->Name = Name;
}

void VActorComponent::SetOwner(VSceneObject* SceneObject) {
	this->Owner = SceneObject;
}

void VActorComponent::Update(double deltaT)
{

}

void VActorComponent::OnInitialize()
{

}

VActorComponent::~VActorComponent()
{
}
