#pragma once

#include <glm/glm.hpp>

#include "VActorComponent.h"

class VSceneComponent : public VActorComponent
{
public:
	VSceneComponent(VScene* Scene);

	glm::mat4 GetModelMatrix();

	void Translate(glm::vec3 vector);

	glm::mat4 GetTransformationMatrix();
	void SetTransformationMatrix(glm::mat4 TransformationMatrix);

	virtual void RenderPass(class VShader* Shader, glm::mat4 ParentModelMatrix);

	virtual void Draw(glm::mat4 ParentModelMatrix);

	virtual  ~VSceneComponent();

protected:
	glm::mat4 ModelMatrix = glm::mat4();
	glm::mat4 TranslationMatrix = glm::mat4();
	glm::mat4 RotationMatrix = glm::mat4();
	glm::mat4 ScaleMatrix = glm::mat4();

	glm::mat4 TransformationMatrix = glm::mat4();
};

