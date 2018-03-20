#include "VActor.h"

#include "../Utils/Assimp/VAssimpUtils.h"
#include "Components/VMeshComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VScene.h"
#include "../Utils/PhysxUtils.h"

#include <stdio.h>

VActor::VActor(VScene* Scene)
{
	this->Scene = Scene;
}

glm::vec3 VActor::GetScale()
{
	return Scale;
}

glm::mat4 VActor::GetModelMatrix()
{
	return translate(glm::mat4(), this->Position)*glm::toMat4(this->Rotation)*glm::scale(glm::mat4(), this->Scale);
}

glm::vec3 VActor::GetPosition()
{
	return Position;
}

void VActor::SetPosition(glm::vec3 Position)
{
	this->Position = Position;
}

void VActor::SetRotation(glm::vec3 Rotation)
{
	this->Rotation = glm::quat(Rotation);
}

void VActor::SetScale(glm::vec3 Scale)
{
	this->Scale = Scale;
}

PxRigidDynamic* VActor::SetRigidDynamic()
{
	if (this->RigidActor != nullptr)
	{
		this->Scene->GetPhysicsScene()->removeActor(*this->RigidActor);
	}
	
	PxRigidDynamic* DynamicActor = VPhysics::GetInstance()->CreateDefaultRigidDynamic(PhysxUtils::ConvertGVecQuatToPxTransform(Position, Rotation));
	this->RigidActor = DynamicActor;
	this->Scene->GetPhysicsScene()->addActor(*this->RigidActor);

	return DynamicActor;
}

PxRigidStatic* VActor::SetRigidStatic()
{
	if (this->RigidActor != nullptr)
	{
		this->Scene->GetPhysicsScene()->removeActor(*this->RigidActor);
	}

	PxRigidStatic* StaticActor = VPhysics::GetInstance()->CreateDefaultRigidStatic(PhysxUtils::ConvertGVecQuatToPxTransform(Position, Rotation));
	this->RigidActor = StaticActor;
	this->Scene->GetPhysicsScene()->addActor(*this->RigidActor);

	return StaticActor;
}

void VActor::Update()
{
	if (this->RigidActor != nullptr && bPhysics)
	{
		PhysxUtils::ConvertPxTransformToGVecQuat(this->RigidActor->getGlobalPose(), this->Position, this->Rotation);
		//std::cout << "Pose: " << this->RigidDynamic->getGlobalPose().p.x << " " << this->RigidDynamic->getGlobalPose().p.y << " " << this->RigidDynamic->getGlobalPose().p.z + '\n';
	}

	for (VActorComponent* ActorComponent : ActorComponents)
	{
		ActorComponent->Update();
	}
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Update();
	}
	ModelMatrix = GetModelMatrix();
}

void VActor::RenderPass(VShader* Shader)
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->RenderPass(Shader, ModelMatrix);
	}
}

void VActor::Draw()
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Draw(ModelMatrix);
	}
}


VActor::~VActor()
{
}
