#pragma once

#include "VPhysics.h"
#include "VPhysicsActor.h"

class VPhysicsScene
{
public:
	VPhysicsScene(PxScene* Scene, VPhysics* Physics);

	void AddPhysicsActor(VPhysicsActor* PhysicsActor);
	PxScene* GetScene() { return Scene; }

	~VPhysicsScene();

private:
	PxScene * Scene;

	VPhysics* Physics;
};

