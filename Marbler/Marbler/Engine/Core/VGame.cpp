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
	ActiveScene->Update(deltaT);
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
	VScene* Scene = new VScene();
	return Scene;
}

VGame::~VGame()
{
}
