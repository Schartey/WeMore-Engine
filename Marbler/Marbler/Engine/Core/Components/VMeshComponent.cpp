#include "VMeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <iostream>

VMeshComponent::VMeshComponent(std::string path)
{
	LoadScene(path);
}

void VMeshComponent::LoadScene(std::string path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	this->ProcessScene(scene);
}

VMeshComponent::~VMeshComponent()
{
}
