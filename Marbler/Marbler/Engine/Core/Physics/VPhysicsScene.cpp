#include "VPhysicsScene.h"



VPhysicsScene::VPhysicsScene(PxScene* Scene, VPhysics* Physics)
{
	this->Scene = Scene;
	this->Physics = Physics;
}

VPhysicsScene::~VPhysicsScene()
{
}
