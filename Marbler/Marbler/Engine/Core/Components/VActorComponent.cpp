#include "VActorComponent.h"

#include "../VActor.h"

VActorComponent::VActorComponent()
{
}

void VActorComponent::SetOwner(VActor* Actor) {
	this->Owner = Actor;
}

void VActorComponent::Update()
{

}


VActorComponent::~VActorComponent()
{
}
