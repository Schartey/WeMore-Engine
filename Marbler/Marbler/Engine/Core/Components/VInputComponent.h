#pragma once

#include "VActorComponent.h"

#include "glm/glm.hpp"

class VInputComponent : public VActorComponent
{
public:
	VInputComponent(VScene* Scene);

	virtual void OnInitialize();
	void OnForwardPressed();
	void OnBackwardPressed();
	void OnLeftPressed();
	void OnRightPressed();
	void OnUpPressed();
	void OnDownPressed();
	void OnForwardReleased();
	void OnBackwardReleased();
	void OnLeftReleased();
	void OnRightReleased();
	void OnUpReleased();
	void OnDownReleased();

	virtual void Update(double deltaT) override;

	~VInputComponent();

protected:
	float MovementSpeed = 300.0f;
	glm::vec3 MovementVector = glm::vec3();
};

