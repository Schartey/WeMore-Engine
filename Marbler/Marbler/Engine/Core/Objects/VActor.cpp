#include "VActor.h"

#include "VScene.h"
#include "../../Utils/Assimp/VAssimpUtils.h"
#include "../Components/VMeshComponent.h"
#include "../../Utils/PhysxUtils.h"

#include <stdio.h>

VActor::VActor(VScene* Scene, std::string Name) : VSceneObject(Scene, Name)
{
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
}

VActor::~VActor()
{
}
