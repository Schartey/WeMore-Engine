#include "VActor.h"



VActor::VActor()
{
}

void VActor::Update()
{
	for (VActorComponent* ActorComponent : ActorComponents)
	{
		ActorComponent->Update();
	}
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Update();
	}
}

void VActor::Draw()
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Draw();
	}
}


VActor::~VActor()
{
}
