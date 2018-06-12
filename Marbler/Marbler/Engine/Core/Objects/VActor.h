#pragma once

#include "VSceneObject.h"

#include "../Physics/VPhysics.h"

class VActor : public VSceneObject
{
public:
	VActor(VScene* Scene, std::string Name);

	bool bPhysics = false;

	virtual void SetPosition(glm::vec3 Position) override;

	PxRigidActor* GetRigidActor()
	{
		return RigidActor;
	}

	glm::vec3 GetMovementVector();

	PxRigidDynamic* SetRigidDynamic();
	PxRigidStatic* SetRigidStatic();

	virtual void Update(double deltaT);
	~VActor();

private:
	PxRigidActor* RigidActor;
};

