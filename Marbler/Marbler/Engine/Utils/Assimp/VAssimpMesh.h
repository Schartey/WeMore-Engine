#pragma once

#include "glm/gtx/quaternion.hpp"

#include "../../Engine/Core/Asset/VMesh.h"
#include "../../Engine/Core/Asset/VMaterial.h"

class VAssimpMesh
{
public:
	VAssimpMesh(VMesh* Mesh, VMaterial* Material, glm::mat4 Transform);

	VMesh* GetMesh();
	VMaterial* GetMaterial();
	glm::vec3 GetPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();

	~VAssimpMesh();

private:
	VMesh * Mesh;
	VMaterial* Material;
	glm::vec3 Position;
	glm::quat Rotation;
	glm::vec3 Scale;
};

