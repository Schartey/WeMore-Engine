#pragma once

#include "PxPhysicsAPI.h"

#define PVD_HOST "127.0.0.1"

using namespace physx;

class VPhysics
{
public:
	VPhysics();

	bool Initialize();
	PxPhysics* GetPxPhysics();

	~VPhysics();

private:
	PxDefaultAllocator Allocator;
	PxDefaultErrorCallback ErrorCallback;

	PxFoundation* Foundation = NULL;
	PxPvd* Pvd = NULL;
	PxPhysics* Physics = NULL;
};

