#include "VPhysicsScene.h"



VPhysicsScene::VPhysicsScene(PxScene* Scene, VPhysics* Physics)
{
	this->Scene = Scene;
	this->Physics = Physics;
}

PxRigidDynamic* VPhysicsScene::CreateDynamic(const PxTransform& t)
{
	PxRigidDynamic* dynamic = this->Physics->GetPxPhysics()->createRigidDynamic(t);
	Scene->addActor(*dynamic);
	return dynamic;
}


VPhysicsScene::~VPhysicsScene()
{
}
