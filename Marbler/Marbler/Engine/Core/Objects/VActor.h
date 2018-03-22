#pragma once

#include "VSceneObject.h"

#include "../Physics/VPhysics.h"

class VActor : public VSceneObject
{
public:
	VActor(VScene* Scene, std::string Name);

	bool bPhysics = false;

	PxRigidActor* GetRigidActor()
	{
		return RigidActor;
	}

	PxRigidDynamic* SetRigidDynamic();
	PxRigidStatic* SetRigidStatic();

	virtual void Update(double deltaT);
	~VActor();

private:
	PxRigidActor* RigidActor;
};

