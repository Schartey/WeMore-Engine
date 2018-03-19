#pragma once

#include "VPhysics.h"
#include "VPhysicsShape.h"

class VActor;

class VPhysicsActor
{
public:
	VPhysicsActor();
	
	void CreateRigidBody(VActor* Actor);
	void AttachPhysicsShape(VPhysicsShape* PhysicsShape);
	PxRigidDynamic* GetRigidBody();
	void SetRigidBody(PxRigidDynamic* RigidBody);

	glm::mat4 GetTransformation();

	~VPhysicsActor();

private:
	PxRigidDynamic* RigidBody;

	VPhysics* Physics;
};

