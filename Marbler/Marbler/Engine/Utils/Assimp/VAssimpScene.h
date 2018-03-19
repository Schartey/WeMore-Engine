#pragma once

#include <vector>
#include "VAssimpMesh.h"

class VAssimpScene
{
public:
	VAssimpScene();

	void AddMesh(VAssimpMesh* Mesh);
	std::vector<VAssimpMesh*> GetMeshes();

	~VAssimpScene();

private:
	std::vector<VAssimpMesh*> Meshes;
};

