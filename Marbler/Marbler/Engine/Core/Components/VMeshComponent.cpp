#include "VMeshComponent.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "../../Utils/Assimp/VAssimpUtils.h"
#include "../../Utils/PhysxUtils.h"

#include "../Objects/VScene.h"
#include "VCameraComponent.h"
#include "../VGameStatics.h"
#include "../VGame.h"

VMeshComponent::VMeshComponent(VScene* Scene, std::string Name) : VSceneComponent(Scene, Name)
{
}

void VMeshComponent::LoadMesh(std::string MeshPath)
{
	VAssimpMesh* AssimpMesh = VAssimpUtils::LoadMesh(this->Scene, MeshPath);
	this->SetMesh(AssimpMesh->GetMesh());
	this->SetMaterial(AssimpMesh->GetMaterial());
	/*this->SetPosition(AssimpMesh->GetPosition());
	this->SetRotation(AssimpMesh->GetRotation());
	this->SetScale(AssimpMesh->GetScale());
	*/
	
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

PxShape* VMeshComponent::GeneratePhysicsShape(GeometryType geometryType)
{
	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);

	if (ActorOwner != nullptr && ActorOwner->GetRigidActor() != nullptr) {
		glm::vec3 BoxHalfExtent = (this->Mesh->GetBoundingBox().max - this->Mesh->GetBoundingBox().min);
		BoxHalfExtent *= Owner->GetScale();
		BoxHalfExtent *= Scale;
		BoxHalfExtent /= 2;

		PhysicsMaterial = VPhysics::GetInstance()->GetPxPhysics()->createMaterial(0.5, 0.5, 0.6);

		switch (geometryType)
		{
		case Box:

			this->PhysicsShape = VPhysics::GetInstance()->GetPxPhysics()->createShape(PxBoxGeometry(PhysxUtils::ConvertGVec3ToPxVec3(BoxHalfExtent)), *PhysicsMaterial);
			this->PhysicsShape->setLocalPose(PhysxUtils::ConvertGVecQuatToPxTransform(this->Position, this->Rotation));
			ActorOwner->GetRigidActor()->attachShape(*this->PhysicsShape);
			this->SetBPhysics(bPhysics);
			break;
		case Sphere:
			this->PhysicsShape = VPhysics::GetInstance()->GetPxPhysics()->createShape(PxSphereGeometry(PhysxUtils::ConvertGVec3ToPxVec3(BoxHalfExtent).x), *PhysicsMaterial);
			this->PhysicsShape->setLocalPose(PhysxUtils::ConvertGVecQuatToPxTransform(this->Position, this->Rotation));
			ActorOwner->GetRigidActor()->attachShape(*this->PhysicsShape);
			this->SetBPhysics(bPhysics);
			break;
		case Cylinder:
			this->PhysicsShape = VPhysics::GetInstance()->GetPxPhysics()->createShape(PxCapsuleGeometry(BoxHalfExtent.y/2, BoxHalfExtent.x), *PhysicsMaterial);
			this->PhysicsShape->setLocalPose(PhysxUtils::ConvertGVecQuatToPxTransform(this->Position, this->Rotation));
			ActorOwner->GetRigidActor()->attachShape(*this->PhysicsShape);
			this->SetBPhysics(bPhysics);
			break;
		}
	}
	return this->PhysicsShape;
}

PxShape* VMeshComponent::GetPhysicsShape()
{
	return this->PhysicsShape;
}

void VMeshComponent::SetBPhysics(bool bPhysics)
{
	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);

	this->bPhysics = bPhysics;
	ActorOwner->GetRigidActor()->detachShape(*this->PhysicsShape);
	this->PhysicsShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, bPhysics);
	ActorOwner->GetRigidActor()->attachShape(*this->PhysicsShape);
}

void VMeshComponent::AttachBasicPhysicsShape(PxBoxGeometry Geometry, PxMaterial* Material)
{
}

void VMeshComponent::SetScale(glm::vec3 Scale)
{
	VSceneComponent::SetScale(Scale);

	VActor* ActorOwner = dynamic_cast<VActor*>(this->Owner);

	if (this->PhysicsShape != nullptr)
	{
		glm::vec3 BoxHalfExtent = (this->Mesh->GetBoundingBox().max - this->Mesh->GetBoundingBox().min);
		BoxHalfExtent *= Owner->GetScale();
		BoxHalfExtent *= Scale;
		BoxHalfExtent /= 2;

		ActorOwner->GetRigidActor()->detachShape(*this->PhysicsShape);
		this->PhysicsShape->setGeometry(PxBoxGeometry(PhysxUtils::ConvertGVec3ToPxVec3(BoxHalfExtent)));
		ActorOwner->GetRigidActor()->attachShape(*this->PhysicsShape);

	}
}

void VMeshComponent::Update(double deltaT)
{
	VSceneComponent::Update(deltaT);
	if (bPhysics)
	{
		PhysxUtils::ConvertPxTransformToGVecQuat(this->PhysicsShape->getLocalPose(), this->Position, this->Rotation);
	}

}

void VMeshComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix, RenderPassBufferType Type)
{
	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();

	if (CameraComponent->IsWithinFrustum(this->Mesh->GetBoundingBox()) || !VGameStatics::GetGame()->GetFrustumCulling()) {
		glm::mat4 CMT = ParentModelMatrix * ModelMatrix;

		VSceneComponent::RenderPass(Shader, CMT, Type);

		if (this->Mesh != nullptr)
		{
			//Don't use local Shader, already set by GBuffer, but add information
			if (Type != ShadowBuffer)
			{
				Material->ApplyRenderPassInformation(Shader);
			}
			
			glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "cmt"), 1, GL_FALSE, glm::value_ptr(CMT));
			
			//ModelMatrix = ParentModelMatrix * TranslationMatrix * RotationMatrix*ScaleMatrix;
			Mesh->RenderPass();
		}
	}
}

void VMeshComponent::Draw(glm::mat4 ParentModelMatrix)
{
	glm::mat4 CMT = ParentModelMatrix * ModelMatrix;

	VSceneComponent::Draw(CMT);

	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();

	if (this->Mesh != nullptr)
	{
		Material->GetShader()->useShader();
		Material->ApplyRenderPassInformation(Material->GetShader());

		glUniformMatrix4fv(glGetUniformLocation(Material->GetShader()->programHandle, "cmt"), 1, GL_FALSE, glm::value_ptr(CMT));
		glUniformMatrix4fv(glGetUniformLocation(Material->GetShader()->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(Material->GetShader()->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

		Mesh->Draw();
	}
}

VMeshComponent::~VMeshComponent()
{
}
