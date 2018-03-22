#pragma once

#include <string>
#include <iostream>

#include "assimp/Scene.h"

#include "VAssimpScene.h"
#include "../../Core/Asset/VMesh.h"
#include "../../Core/Asset/VDirectionalLight.h"
//#include "../../Core/Asset/VPointLight.h"

class VAssimpUtils
{
public:
	VAssimpUtils();

	static VAssimpScene* LoadScene(VScene* Scene, std::string path, std::string filename);
	static VAssimpMesh* LoadMesh(VScene* Scene, std::string filePath);
	//static VPointLight* LoadPointLight(std::string filePath);
	static VDirectionalLight* LoadDirectionalLight(std::string filePath);

	~VAssimpUtils();

private:
	static void ProcessScene(VScene* Scene, std::string path, VAssimpScene* AssimpScene, const aiScene* iscene);
	static void ProcessNode(VScene* Scene, std::string path, VAssimpScene* AssimpScene, const aiNode* Node, const aiScene* iscene);
	static VAssimpMesh* ProcessMesh(VScene* Scene, std::string path, VAssimpScene* AssimpScene, aiMesh* mesh, const aiNode* node, const aiScene* iscene);
	static VMaterial* ProcessMaterial(std::string path, aiMaterial* Material);

	static glm::mat4 ConvertMat4(const aiMatrix4x4 mat);
};

