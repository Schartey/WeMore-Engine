#include "VAssimpScene.h"



VAssimpScene::VAssimpScene()
{
}

void VAssimpScene::AddMesh(VMesh* Mesh)
{
	Meshes.push_back(Mesh);
}

std::vector<VMesh*> VAssimpScene::GetMeshes()
{
	return Meshes;
}

VAssimpScene::~VAssimpScene()
{
}
