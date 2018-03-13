#include "VScene.h"

VScene::VScene()
{
}

void VScene::Update()
{
	for (VActor* Actor : Actors)
	{
		Actor->Update();
	}
}

void VScene::Draw()
{
	for (VActor* Actor : Actors)
	{
		Actor->Draw();
	}
}

VScene::~VScene()
{
}
