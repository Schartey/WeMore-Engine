#pragma once

#include "glm/glm.hpp"
#include "VSceneComponent.h"
#include "../Asset/VMesh.h"
#include "../VFrustum.h"

class VCameraComponent : public VSceneComponent
{
public:
	VCameraComponent(VScene* Scene, std::string Name);

	float GetPhi();
	float GetTheta();
	void IncreasePhi(float Phi);
	void IncreaseTheta(float Theta);

	glm::vec3 GetForward();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetModel() { return Model; }
	glm::mat4 GetProjectionMatrix();
	VFrustum* GetFrustum();
	void SetTarget(VSceneComponent* SceneComponent);
	void SetProjectionMatrix(float Fov, int Width, int Height, float NearPlane, float FarPlane);

	virtual void Update(double deltaT) override;
	virtual ~VCameraComponent();

private:
	bool bHasTarget;
	float LastCameraInteractionTime = 0.0f;
	float CameraSwitchTime = 3000.0f;
	float BlendSpeed = 1.0f;
	VSceneComponent* Target;
	VFrustum* Frustum;

	glm::mat4 ViewMatrix = glm::mat4();
	glm::mat4 ProjectionMatrix = glm::mat4();
	glm::vec3 LookAt = glm::vec3();
	glm::mat4 Model = glm::mat4();

	float Phi;
	float Theta;

	float Fov;
	float NearPlane;
	float FarPlane;
	float Ratio;
	float WidthNear;
	float HeightNear;
	float WidthFar;
	float HeightFar;
};

