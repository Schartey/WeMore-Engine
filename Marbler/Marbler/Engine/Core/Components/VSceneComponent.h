#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VActorComponent.h"
#include "../../Utils/BufferUtils.h"

class VSceneComponent : public VActorComponent
{
public:
	VSceneComponent(VScene* Scene, std::string Name);

	glm::mat4 GetGlobalModelMatrix();
	glm::mat4 GetModelMatrix();

	glm::vec3 GetPosition();
	glm::vec3 GetGlobalPosition();
	glm::quat GetGlobalRotation();
	void SetPosition(glm::vec3 Position);
	void SetRotation(glm::vec3 Rotation);
	void SetRotation(glm::quat Rotation);
	void SetScale(glm::vec3 Scale);

	virtual void Update(double deltaT);
	virtual void RenderPass(class VShader* Shader, glm::mat4 ParentModelMatrix, RenderPassBufferType Type);

	virtual void Draw(glm::mat4 ParentModelMatrix);

	virtual  ~VSceneComponent();

protected:
	glm::mat4 ModelMatrix = glm::mat4();

	glm::vec3 Position = glm::vec3();
	glm::quat Rotation = glm::quat();
	glm::vec3 Scale = glm::vec3(1.0f);
};

