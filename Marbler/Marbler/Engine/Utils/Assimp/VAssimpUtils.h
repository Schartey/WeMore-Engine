#pragma once

#include <string>
#include <iostream>

#include "assimp/Scene.h"

#include "VAssimpScene.h"
#include "../../Core/Asset/VMesh.h"

class VAssimpUtils
{
public:
	VAssimpUtils();

	static VAssimpScene* LoadScene(VScene* Scene, std::string path, std::string filename);

	~VAssimpUtils();

private:
	static void ProcessScene(VScene* Scene, std::string path, VAssimpScene* AssimpScene, const aiScene* iscene);
	static void ProcessNode(VScene* Scene, std::string path, VAssimpScene* AssimpScene, const aiNode* Node, const aiScene* iscene);
	static VMesh* ProcessMesh(VScene* Scene, std::string path, VAssimpScene* AssimpScene, aiMesh* mesh, const aiNode* node, const aiScene* iscene);
	static VMaterial* ProcessMaterial(std::string path, aiMaterial* Material);

	static glm::mat4 ConvertMat4(const aiMatrix4x4 mat);
};

