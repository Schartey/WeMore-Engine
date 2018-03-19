#pragma once

#include "VPhysics.h"

class VPhysicsActor
{
public:
	VPhysicsActor(VPhysics* Physics);

	PxShape* CreatePhysicsShapeSphere(const PxTransform& t);

	void SetRigidBody(PxRigidDynamic* RigidBody);

	~VPhysicsActor();

private:
	PxRigidDynamic* RigidBody;

	VPhysics* Physics;
};

