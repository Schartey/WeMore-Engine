#include "VObjectPool.h"



VObjectPool::VObjectPool()
{
}

int VObjectPool::AddTexture(VTexture* Texture)
{
	Textures.insert(std::pair<int, VTexture*>(++TextureCount, Texture));

	return TextureCount;
}

int VObjectPool::CreateScene(std::string name)
{
	VScene* Scene = new VScene(name);
	Scenes.insert(std::pair<int, VScene*>(++SceneCount, Scene));

	return SceneCount;
}

int VObjectPool::AddActor(VActor* Actor)
{
	SceneObjects.insert(std::pair<int, VActor*>(++SceneObjectCount, Actor));

	return SceneObjectCount;
}

int VObjectPool::AddComponent(VActorComponent* Component)
{
	ActorComponents.insert(std::pair<int, VActorComponent*>(++ActorComponentCount, Component));

	return ActorComponentCount;
}

VTexture* VObjectPool::GetTexture(int id)
{
	return Textures.at(id);
}

VScene* VObjectPool::GetSceneById(int id)
{
	return Scenes.at(id);
}

VObjectPool::~VObjectPool()
{
}
