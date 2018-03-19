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
	VMeshComponent(VScene* Scene);

	void LoadMesh(std::string MeshPath, std::string MeshFileName);
	VMesh* GetMesh();
	VMaterial* GetMaterial();
	VPhysicsShape* GetPhysicsShape();

	void SetMesh(VMesh* Mesh);
	void SetMaterial(VMaterial* Material);

	void AttachBasicPhysicsShape(PxBoxGeometry Geometry, PxMaterial* Material);

	void Translate(glm::vec3 TranslationVector);
	void Scale(glm::vec3 ScaleVector);

	virtual void RenderPass(class VShader* Shader, glm::mat4 ParentModelMatrix) override;
	virtual void Draw(glm::mat4 ParentModelMatrix) override;

	virtual ~VMeshComponent();

private:
	VMesh * Mesh;
	VMaterial* Material;

	VPhysicsShape* PhysicsShape;
};

