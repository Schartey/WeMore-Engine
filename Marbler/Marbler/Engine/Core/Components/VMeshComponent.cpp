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

void VMeshComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix)
{
	VSceneComponent::RenderPass(Shader, ModelMatrix);

	if (this->Mesh != nullptr)
	{
		ModelMatrix = ParentModelMatrix * TranslationMatrix * RotationMatrix*ScaleMatrix;
		Mesh->RenderPass(Shader, ModelMatrix);
	}
}

void VMeshComponent::Draw(glm::mat4 ParentModelMatrix)
{
	VSceneComponent::Draw(ModelMatrix);

	if (this->Mesh != nullptr)
	{
		ModelMatrix = ParentModelMatrix * TranslationMatrix * RotationMatrix*ScaleMatrix;
		Mesh->Draw(ModelMatrix);
	}
}

VMeshComponent::~VMeshComponent()
{
}
