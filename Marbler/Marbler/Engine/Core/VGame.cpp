#include "VGame.h"

#include "Physics/VPhysicsScene.h"

VGame::VGame()
{
}

void VGame::OnInitialize()
{

}

void VGame::Update(double deltaT)
{
	ActiveScene->Update();
}

void VGame::RenderPass(VShader* Shader)
{
	ActiveScene->RenderPass(Shader);
}

void VGame::Draw()
{
	ActiveScene->Draw();
}

void VGame::SetWindow(VWindow* Window)
{
	this->Window = Window;
}

void VGame::SetPhysics(VPhysics* Physics)
{
	this->Physics = Physics;
}

VScene* VGame::GetActiveScene()
{
	return ActiveScene;
}

void VGame::SetActiveScene(VScene* Scene)
{
	ActiveScene = Scene;
}

VScene* VGame::CreateScene()
{
	PxSceneDesc sceneDesc(Physics->GetPxPhysics()->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	PxDefaultCpuDispatcher*	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	PxScene* PScene = Physics->GetPxPhysics()->createScene(sceneDesc);

	VPhysicsScene* PhysicsScene = new VPhysicsScene(PScene, Physics);

	VScene* Scene = new VScene(PhysicsScene);

	return Scene;
}

VGame::~VGame()
{
}
