#pragma once

#include "VSceneComponent.h"
#include "../Asset/VMaterial.h"
#include "../Asset/VMesh.h"
#include <string>
#include <vector>
#include "assimp/Scene.h"

#include "../Physics/VPhysics.h"

class VMeshComponent : public VSceneComponent
{
public:
	VMeshComponent(VScene* Scene);

	void LoadMesh(std::string MeshPath, std::string MeshFileName);

	VMesh* GetMesh();
	VMaterial* GetMaterial();
	PxShape* GetPhysicsShape();

	void SetMesh(VMesh* Mesh);
	void SetMaterial(VMaterial* Material);
	void SetBPhysics(bool bPhysics);

	void AttachBasicPhysicsShape(PxBoxGeometry Geometry, PxMaterial* Material);

	void SetScale(glm::vec3 ScaleVector);

	virtual void Update() override;
	virtual void RenderPass(class VShader* Shader, glm::mat4 ParentModelMatrix) override;
	virtual void Draw(glm::mat4 ParentModelMatrix) override;

	virtual ~VMeshComponent();

private:
	bool bPhysics = false;

	VMesh * Mesh;
	VMaterial* Material;

	PxMaterial* PhysicsMaterial;
	PxShape* PhysicsShape;
	//VPhysicsShape* PhysicsShape;
};

