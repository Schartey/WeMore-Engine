#include "VActorComponent.h"

#include "../VActor.h"

VActorComponent::VActorComponent(VScene* Scene)
{
	this->Scene = Scene;
}

void VActorComponent::SetOwner(VActor* Actor) {
	this->Owner = Actor;
}

void VActorComponent::Update()
{

}

void VActorComponent::OnInitialize()
{

}

VActorComponent::~VActorComponent()
{
}
