#include "VMeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../../Utils/Assimp/VAssimpUtils.h"
#include "../../Utils/PhysxUtils.h"

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
	//this->SetTransformationMatrix(AssimpMesh->GetTransformation());

	if(this->Owner->GetRigidActor<PxRigidActor>() != nullptr) { 
		glm::vec3 BoxHalfExtent = (this->Mesh->GetBoundingBox().max - this->Mesh->GetBoundingBox().min);
		BoxHalfExtent *= Owner->GetScale();
		BoxHalfExtent *= Scale;
		BoxHalfExtent /= 2;

		PhysicsMaterial = VPhysics::GetInstance()->GetPxPhysics()->createMaterial(0.5, 0.5, 0.6);
		this->PhysicsShape = VPhysics::GetInstance()->CreateDefaultPhysicsShape(PxBoxGeometry(PhysxUtils::ConvertGVec3ToPxVec3(BoxHalfExtent)), PhysicsMaterial);
		this->PhysicsShape->setLocalPose(PhysxUtils::ConvertGVecQuatToPxTransform(this->Position, this->Rotation));
		this->Owner->GetRigidActor<PxRigidActor>()->attachShape(*this->PhysicsShape);
		this->SetBPhysics(bPhysics);
	}
}

VMesh* VMeshComponent::GetMesh()
{
	return this->Mesh;
}

VMaterial* VMeshComponent::GetMaterial()
{
	return this->Material;
}

void VMeshComponent::SetMesh(VMesh* Mesh)
{
	this->Mesh = Mesh;
}

void VMeshComponent::SetMaterial(VMaterial* Material)
{
	this->Material = Material;
}

PxShape* VMeshComponent::GetPhysicsShape()
{
	return this->PhysicsShape;
}

void VMeshComponent::SetBPhysics(bool bPhysics)
{
	this->bPhysics = bPhysics;
	this->Owner->GetRigidActor<PxRigidActor>()->detachShape(*this->PhysicsShape);
	this->PhysicsShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, bPhysics);
	this->Owner->GetRigidActor<PxRigidActor>()->attachShape(*this->PhysicsShape);
}

void VMeshComponent::AttachBasicPhysicsShape(PxBoxGeometry Geometry, PxMaterial* Material)
{
}

void VMeshComponent::SetScale(glm::vec3 Scale)
{
	VSceneComponent::SetScale(Scale);

	glm::vec3 BoxHalfExtent = (this->Mesh->GetBoundingBox().max - this->Mesh->GetBoundingBox().min);
	BoxHalfExtent *= Owner->GetScale();
	BoxHalfExtent *= Scale;
	BoxHalfExtent /= 2;

	this->Owner->GetRigidActor<PxRigidActor>()->detachShape(*this->PhysicsShape);
	this->PhysicsShape->setGeometry(PxBoxGeometry(PhysxUtils::ConvertGVec3ToPxVec3(BoxHalfExtent)));
	this->Owner->GetRigidActor<PxRigidActor>()->attachShape(*this->PhysicsShape);
}

void VMeshComponent::Update()
{
	if (bPhysics)
	{
		PhysxUtils::ConvertPxTransformToGVecQuat(this->PhysicsShape->getLocalPose(), this->Position, this->Rotation);
	}
	ModelMatrix = translate(glm::mat4(), this->Position)*glm::toMat4(this->Rotation)*glm::scale(glm::scale(glm::mat4(), this->Scale), Owner->GetScale());
}

void VMeshComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix)
{
	glm::mat4 CMT = ParentModelMatrix * ModelMatrix;

	VSceneComponent::RenderPass(Shader, CMT);

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
		Mesh->Draw(ModelMatrix);
	}
}

VMeshComponent::~VMeshComponent()
{
}
