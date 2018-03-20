#include "VPhysics.h"

VPhysics* VPhysics::instance = 0;

VPhysics::VPhysics()
{
}

bool VPhysics::Initialize()
{
	Foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, Allocator, ErrorCallback);

	Pvd = PxCreatePvd(*Foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	Pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *Foundation, PxTolerancesScale(), true, Pvd);
	return true;
}

PxPhysics* VPhysics::GetPxPhysics()
{
	return Physics;
}

PxScene* VPhysics::CreateDefaultScene()
{
	PxSceneDesc sceneDesc(Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	PxDefaultCpuDispatcher* gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	return Physics->createScene(sceneDesc);
}

PxShape* VPhysics::CreateDefaultPhysicsShape(PxBoxGeometry Geometry, PxMaterial* Material)
{
	return Physics->createShape(Geometry, *Material);
}

PxRigidDynamic* VPhysics::CreateDefaultRigidDynamic(PxTransform Transform)
{
	PxRigidDynamic* RigidBody = Physics->createRigidDynamic(Transform);

	return RigidBody;
}

PxRigidStatic* VPhysics::CreateDefaultRigidStatic(PxTransform Transform)
{
	PxRigidStatic* RigidBody = Physics->createRigidStatic(Transform);

	return RigidBody;
}