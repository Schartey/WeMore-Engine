#include "VMeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

VMeshComponent::VMeshComponent()
{

}

void VMeshComponent::SetMesh(VMesh* Mesh)
{
	this->Mesh = Mesh;
}

void VMeshComponent::SetPhysicsShape(VPhysicsShape* PhysicsShape)
{
	this->PhysicsShape = PhysicsShape;
}

void VMeshComponent::Translate(glm::vec3 TranslationVector)
{
	TranslationMatrix = glm::translate(TranslationMatrix, TranslationVector);
}

void VMeshComponent::Scale(glm::vec3 ScaleVector)
{
	ScaleMatrix = glm::scale(ScaleMatrix, ScaleVector);
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
