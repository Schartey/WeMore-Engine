#pragma once

#include <vector>
#include "../../Core/Asset/VMesh.h"

class VAssimpScene
{
public:
	VAssimpScene();

	void AddMesh(VMesh* Mesh);
	std::vector<VMesh*> GetMeshes();

	~VAssimpScene();

private:
	std::vector<VMesh*> Meshes;
};

