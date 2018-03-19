#pragma once

#include "VActorComponent.h"

class VInputComponent : public VActorComponent
{
public:
	VInputComponent();

	virtual void OnInitialize();
	void OnForward();

	~VInputComponent();
};

