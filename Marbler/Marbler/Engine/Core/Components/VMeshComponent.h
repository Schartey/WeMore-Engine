#pragma once

#include "VSceneComponent.h"
#include "../Asset/VMaterial.h"
#include <string>
#include "assimp/Scene.h"

class VMeshComponent : VSceneComponent
{
public:
	VMeshComponent(std::string Path);

	VMaterial GetMaterial();

	~VMeshComponent();

private:
	void LoadScene(std::string Path);
	void ProcessScene(const aiScene* Scene);

};

