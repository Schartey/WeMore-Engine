#include "VPhysics.h"

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

VPhysics::~VPhysics()
{
}
