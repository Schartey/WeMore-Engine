#pragma once

#include "VPhysics.h"

class VPhysicsScene
{
public:
	VPhysicsScene(PxScene* Scene, VPhysics* Physics);

	PxScene* GetScene() { return Scene; }

	~VPhysicsScene();

private:
	PxScene * Scene;

	VPhysics* Physics;
};

