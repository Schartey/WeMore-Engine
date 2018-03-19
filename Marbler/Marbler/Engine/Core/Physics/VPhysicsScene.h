#pragma once

#include "VPhysics.h"

class VPhysicsScene
{
public:
	VPhysicsScene(PxScene* Scene, VPhysics* Physics);

	PxRigidDynamic* CreateDynamic(const PxTransform& t);

	~VPhysicsScene();

private:
	PxScene * Scene;

	VPhysics* Physics;
};

