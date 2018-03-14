#pragma once

#include <glm/glm.hpp>

#include "VActorComponent.h"

class VSceneComponent : public VActorComponent
{
public:
	VSceneComponent();

	void Translate(glm::vec3 vector);

	virtual void Draw(glm::mat4 ParentModelMatrix);

	virtual  ~VSceneComponent();

protected:
	glm::mat4 ModelMatrix = glm::mat4();
	glm::mat4 TranslationMatrix = glm::mat4();
	glm::mat4 RotationMatrix = glm::mat4();
	glm::mat4 ScaleMatrix = glm::mat4();
};

