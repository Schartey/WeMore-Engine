#pragma once

#include "VActorComponent.h"

#include "glm/glm.hpp"

class VInputComponent : public VActorComponent
{
public:
	VInputComponent(VScene* Scene, std::string Name);

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
	void OnSpaceBarPressed();
	void OnMPressed();
	void OnF1Pressed();
	void OnF2Pressed();
	void OnF3Pressed();
	void OnF4Pressed();
	void OnF8Pressed();

	void OnQuitPressed();

	void ChangeInputMode(bool InputMode);

	void SetJumpForce(float JumpForce);
	void SetMovementSpeed(float MovementSpeed);
	void SetMaxSpeed(float MaxSpeed);

	void OnMouseMoved(double deltaX, double deltaY);

	virtual void Update(double deltaT) override;

	~VInputComponent();

protected:
	bool InputMode;
	VScene * Scene;
	float MaxSpeed = 7.0f;
	float MovementSpeed = 10.0f;
	float JumpForce = 300.0f;
	glm::vec3 MovementVector = glm::vec3();
};

