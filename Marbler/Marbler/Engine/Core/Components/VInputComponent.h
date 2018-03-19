#pragma once

#include "VActorComponent.h"

class VInputComponent : public VActorComponent
{
public:
	VInputComponent(VScene* Scene);

	virtual void OnInitialize();
	void OnForward();
	void Turn();

	~VInputComponent();
};

