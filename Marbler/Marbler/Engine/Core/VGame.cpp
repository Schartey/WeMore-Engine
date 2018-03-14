#include "VGame.h"

VGame::VGame()
{
}

void VGame::OnInitialize()
{

}

void VGame::Update()
{
	ActiveScene->Update();
}

void VGame::Draw()
{
	ActiveScene->Draw();
}

void VGame::SetWindow(VWindow* Window)
{
	this->Window = Window;
}

void VGame::SetActiveScene(VScene* Scene)
{
	ActiveScene = Scene;
}

VGame::~VGame()
{
}
