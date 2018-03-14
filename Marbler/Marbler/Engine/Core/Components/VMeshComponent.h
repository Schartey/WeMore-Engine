#pragma once

#include "VSceneComponent.h"
#include "../Asset/VMaterial.h"
#include "../Asset/VMesh.h"
#include <string>
#include <vector>
#include "assimp/Scene.h"

class VMeshComponent : public VSceneComponent
{
public:
	VMeshComponent();

	void SetMesh(VMesh* Mesh);

	virtual void Draw(glm::mat4 ParentModelMatrix) override;

	virtual ~VMeshComponent();

private:
	VMesh * Mesh;
};

