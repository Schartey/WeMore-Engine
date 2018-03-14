#include "VMeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <iostream>

VMeshComponent::VMeshComponent()
{

}

void VMeshComponent::SetMesh(VMesh* Mesh)
{
	this->Mesh = Mesh;
}

void VMeshComponent::Draw()
{
	VSceneComponent::Draw();

	if (this->Mesh != nullptr)
	{
		ModelMatrix = TranslationMatrix * RotationMatrix*ScaleMatrix;
		Mesh->Draw(ModelMatrix);
	}
}

VMeshComponent::~VMeshComponent()
{
}
