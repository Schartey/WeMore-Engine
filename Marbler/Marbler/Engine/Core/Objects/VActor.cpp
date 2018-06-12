#include "VActor.h"

#include "VScene.h"
#include "../../Utils/Assimp/VAssimpUtils.h"
#include "../Components/VMeshComponent.h"
#include "../../Utils/PhysxUtils.h"

#include <stdio.h>

VActor::VActor(VScene* Scene, std::string Name) : VSceneObject(Scene, Name)
{
}

void VActor::SetPosition(glm::vec3 Position)
{
	VSceneObject::SetPosition(Position);

	if (this->RigidActor != nullptr)
	{
		this->RigidActor->setGlobalPose(PxTransform(PhysxUtils::ConvertGVec3ToPxVec3(this->Position)));
	}
}
glm::vec3 VActor::GetMovementVector()
{
	if (this->RigidActor != nullptr)
	{
		return PhysxUtils::ConvertPxVec3ToGVec3(((PxRigidBody*)this->RigidActor)->getLinearVelocity().getNormalized());
	}
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

void VActor::Update(double deltaT)
{
	if (this->RigidActor != nullptr && bPhysics)
	{
		PhysxUtils::ConvertPxTransformToGVecQuat(this->RigidActor->getGlobalPose(), this->Position, this->Rotation);
	}

	VSceneObject::Update(deltaT);

	if (Name._Equal("CameraActor"))
	{
		//std::cout << "Actor X: " << this->Rotation.x << " Y: " << this->Rotation.y << " Z: " << this->Rotation.y << '\n';
	}
}

VActor::~VActor()
{
}
