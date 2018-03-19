#include "VPhysicsActor.h"



VPhysicsActor::VPhysicsActor(VPhysics* Physics)
{
	this->Physics = Physics;
}

PxShape* VPhysicsActor::CreatePhysicsShapeSphere(const PxTransform& t)
{
	PxMaterial* Material = Physics->GetPxPhysics()->createMaterial(0.5f, 0.5f, 0.6f);
	PxShape* shape = Physics->GetPxPhysics()->createShape(PxSphereGeometry(), *Material);
	
	RigidBody->attachShape(*shape);
	shape->release();

	return shape;
}

void VPhysicsActor::SetRigidBody(PxRigidDynamic* RigidBody)
{
	this->RigidBody = RigidBody;
}

VPhysicsActor::~VPhysicsActor()
{
}
