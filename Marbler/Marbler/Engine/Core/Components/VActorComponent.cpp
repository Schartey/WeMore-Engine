#include "VActorComponent.h"

#include "../Objects/VActor.h"

VActorComponent::VActorComponent(VScene* Scene)
{
	this->Scene = Scene;
}

void VActorComponent::SetOwner(VActor* Actor) {
	this->Owner = Actor;
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
