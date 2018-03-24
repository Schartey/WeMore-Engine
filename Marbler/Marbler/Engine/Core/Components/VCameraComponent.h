#pragma once

#include "glm/glm.hpp"
#include "VSceneComponent.h"

class VCameraComponent : public VSceneComponent
{
public:
	VCameraComponent(VScene* Scene, std::string Name);

	float GetPhi();
	float GetTheta();
	void IncreasePhi(float Phi);
	void IncreaseTheta(float Theta);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void SetTarget(VSceneComponent* SceneComponent);
	void SetProjectionMatrix(glm::mat4 ProjectionMatrix);

	virtual void Update(double deltaT) override;
	virtual ~VCameraComponent();

private:
	bool bHasTarget;
	float LastCameraInteractionTime = 0.0f;
	float CameraSwitchTime = 3000.0f;
	float BlendSpeed = 1.0f;
	VSceneComponent* Target;

	glm::mat4 ViewMatrix = glm::mat4();
	glm::mat4 ProjectionMatrix = glm::mat4();
	glm::vec3 LookAt = glm::vec3();

	float Radius = 0.0f;
	float PhiDifference;
	float ThetaDifference;
	float Phi;
	float Theta;

	glm::vec3 up = glm::vec3(0,1,0);
	glm::vec3 right = glm::vec3(0,0,1);

	glm::mat4 Orientation() const;
	glm::vec3 Forward() const;
	glm::vec3 Right() const;
	glm::vec3 Up() const;
};

