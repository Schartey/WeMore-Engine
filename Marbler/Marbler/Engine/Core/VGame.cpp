#include "VGame.h"

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

VScene* VGame::GetActiveScene()
{
	return ActiveScene;
}

void VGame::SetActiveScene(VScene* Scene)
{
	ActiveScene = Scene;
}

VGame::~VGame()
{
}
