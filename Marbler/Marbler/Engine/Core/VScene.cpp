#include "VScene.h"

VScene::VScene()
{
}

VActor* VScene::CreateActor()
{
	VActor* Actor = new VActor(this);

	Actors.push_back(Actor);

	return Actor;
}

VActor* VScene::GetActivePlayerActor()
{
	return ActivePlayerActor;
}

void VScene::SetActivePlayerActor(VActor* Actor)
{
	this->ActivePlayerActor = Actor;
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
