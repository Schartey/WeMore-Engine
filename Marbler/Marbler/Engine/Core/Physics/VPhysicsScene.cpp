#include "VPhysicsScene.h"



VPhysicsScene::VPhysicsScene(PxScene* Scene, VPhysics* Physics)
{
	this->Scene = Scene;
	this->Physics = Physics;
}

void VPhysicsScene::AddPhysicsActor(VPhysicsActor* PhysicsActor)
{
	this->Scene->addActor(*PhysicsActor->GetRigidBody());
}


VPhysicsScene::~VPhysicsScene()
{
}
