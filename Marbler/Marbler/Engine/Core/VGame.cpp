#include "VGame.h"



VGame::VGame()
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

VGame::~VGame()
{
}
