#pragma once

#include "VSceneComponent.h"
#include "../Asset/VMaterial.h"
#include "../Asset/VMesh.h"
#include <string>
#include <vector>
#include "assimp/Scene.h"

#include "../Physics/VPhysicsShape.h"

class VMeshComponent : public VSceneComponent
{
public:
	VMeshComponent();

	void SetMesh(VMesh* Mesh);
	void SetPhysicsShape(VPhysicsShape* PhysicsShape);

	void Translate(glm::vec3 TranslationVector);
	void Scale(glm::vec3 ScaleVector);

	virtual void RenderPass(class VShader* Shader, glm::mat4 ParentModelMatrix) override;
	virtual void Draw(glm::mat4 ParentModelMatrix) override;

	virtual ~VMeshComponent();

private:
	VMesh * Mesh;

	VPhysicsShape* PhysicsShape;
};

