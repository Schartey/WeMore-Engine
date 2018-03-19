#include "VAssimpScene.h"



VAssimpScene::VAssimpScene()
{
}

void VAssimpScene::AddMesh(VAssimpMesh* Mesh)
{
	Meshes.push_back(Mesh);
}

std::vector<VAssimpMesh*> VAssimpScene::GetMeshes()
{
	return Meshes;
}

VAssimpScene::~VAssimpScene()
{
}
