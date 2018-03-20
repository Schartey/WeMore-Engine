#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VActorComponent.h"

class VSceneComponent : public VActorComponent
{
public:
	VSceneComponent(VScene* Scene);

	glm::mat4 GetModelMatrix();

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 Position);
	void SetRotation(glm::vec3 Rotation);
	void SetScale(glm::vec3 Scale);

	virtual void RenderPass(class VShader* Shader, glm::mat4 ParentModelMatrix);

	virtual void Draw(glm::mat4 ParentModelMatrix);

	virtual  ~VSceneComponent();

protected:
	glm::mat4 ModelMatrix = glm::mat4();

	glm::vec3 Position = glm::vec3(1.0f);
	glm::quat Rotation = glm::quat();
	glm::vec3 Scale = glm::vec3(1.0f);
};

