#pragma once

#include "glm/glm.hpp"
#include "VSceneComponent.h"

class VCameraComponent : public VSceneComponent
{
public:
	VCameraComponent();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	void Rotate(glm::vec3 Rotate);
	void SetLookAt(glm::vec3 LookAtVector);
	void SetProjectionMatrix(glm::mat4 ProjectionMatrix);

	virtual ~VCameraComponent();

private:
	glm::mat4 ViewMatrix = glm::mat4();
	glm::mat4 ProjectionMatrix = glm::mat4();
	glm::vec3 LookAt = glm::vec3();

	void UpdateViewMatrix();
};

