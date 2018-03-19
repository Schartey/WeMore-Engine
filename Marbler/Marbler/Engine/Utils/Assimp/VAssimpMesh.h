#pragma once

#include "../../Engine/Core/Asset/VMesh.h"
#include "../../Engine/Core/Asset/VMaterial.h"

class VAssimpMesh
{
public:
	VAssimpMesh(VMesh* Mesh, VMaterial* Material, glm::mat4 Transform);

	VMesh* GetMesh();
	VMaterial* GetMaterial();
	glm::mat4 GetTransformation();

	~VAssimpMesh();

private:
	VMesh * Mesh;
	VMaterial* Material;
	glm::mat4 Transformation;
};

