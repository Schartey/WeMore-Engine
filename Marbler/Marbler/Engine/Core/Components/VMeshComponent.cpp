#include "VMeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../../Utils/Assimp/VAssimpUtils.h"

#include "../VScene.h"
#include "../Components/VCameraComponent.h"

VMeshComponent::VMeshComponent(VScene* Scene) : VSceneComponent(Scene)
{
}

void VMeshComponent::LoadMesh(std::string MeshPath, std::string MeshFileName)
{
	VAssimpMesh* AssimpMesh = VAssimpUtils::LoadMesh(this->Scene, MeshPath, MeshFileName);
	this->SetMesh(AssimpMesh->GetMesh());
	this->SetMaterial(AssimpMesh->GetMaterial());
	this->SetTransformationMatrix(AssimpMesh->GetTransformation());
}

VMesh* VMeshComponent::GetMesh()
{
	return this->Mesh;
}

VMaterial* VMeshComponent::GetMaterial()
{
	return this->Material;
}

VPhysicsShape* VMeshComponent::GetPhysicsShape()
{
	return this->PhysicsShape;
}

void VMeshComponent::SetMesh(VMesh* Mesh)
{
	this->Mesh = Mesh;
}

void VMeshComponent::SetMaterial(VMaterial* Material)
{
	this->Material = Material;
}

void VMeshComponent::AttachBasicPhysicsShape(PxBoxGeometry Geometry, PxMaterial* Material)
{
	PhysicsShape = new VPhysicsShape();
	PhysicsShape->GenerateBasicPhysicsShape(this, Geometry, Material);
	PhysicsShape->SetTransformationMatrix(TransformationMatrix);

	Owner->AddPhysicsShape(PhysicsShape);
}

void VMeshComponent::Translate(glm::vec3 TranslationVector)
{
	TransformationMatrix = glm::translate(TransformationMatrix, TranslationVector);
	if (this->PhysicsShape != nullptr)
	{
		this->PhysicsShape->SetTransformationMatrix(TransformationMatrix);
	}
}

void VMeshComponent::Scale(glm::vec3 ScaleVector)
{
	TransformationMatrix = glm::scale(TransformationMatrix, ScaleVector);
}

void VMeshComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix)
{
	VSceneComponent::RenderPass(Shader, ModelMatrix);

	glm::mat4 CMT = ParentModelMatrix * TransformationMatrix;

	VCameraComponent* CameraComponent = Scene->GetActivePlayerActor()->GetComponentByClass<VCameraComponent>();

	if (this->Mesh != nullptr)
	{
		//Don't use local Shader, already set by GBuffer, but add information
		Material->ApplyRenderPassInformation(Shader);

		glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "cmt"), 1, GL_FALSE, glm::value_ptr(CMT));
		glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

		//ModelMatrix = ParentModelMatrix * TranslationMatrix * RotationMatrix*ScaleMatrix;
		Mesh->RenderPass();
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
