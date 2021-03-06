#pragma once

#include "PxPhysicsAPI.h"

#define PVD_HOST "127.0.0.1"

using namespace physx;

enum GeometryType {
	Box,
	Sphere,
	Cylinder,
	Dynamic
};
class VPhysics
{
public:
	static VPhysics* GetInstance() {
		if (instance == nullptr)
			instance = new VPhysics();

		return instance;
	}

	bool Initialize();
	PxPhysics* GetPxPhysics();
	PxScene* CreateDefaultScene();
	PxRigidDynamic* CreateDefaultRigidDynamic(PxTransform Transform);
	PxRigidStatic* CreateDefaultRigidStatic(PxTransform Transform);

	~VPhysics() { delete instance; }

private:
	VPhysics();

	static VPhysics* instance;

	PxDefaultAllocator Allocator;
	PxDefaultErrorCallback ErrorCallback;

	PxFoundation* Foundation = NULL;
	PxPvd* Pvd = NULL;
	PxPhysics* Physics = NULL;
};

