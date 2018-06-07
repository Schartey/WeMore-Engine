#pragma once

#include <map>

#include "Objects/VSceneObject.h"
#include "Objects/VScene.h"

class VObjectPool
{
public:
	VObjectPool();

	int CreateScene(std::string name);
	int AddTexture(VTexture* Texture);
	int AddActor(VActor* Actor);
	int AddComponent(VActorComponent* Component);

	template <typename T>
	inline T* GetComponent(int id)
	{
		T* Component = dynamic_cast<T*>(ActorComponents.at(id));
		if (Component != nullptr)
		{
			return Component;
		}
		return nullptr;
	}

	template <typename T>
	inline T* GetSceneObject(int id)
	{
		T* SceneObject = dynamic_cast<T*>(SceneObjects.at(id));
		if (SceneObject != nullptr)
		{
			return SceneObject;
		}
		return nullptr;
	}

	VTexture* GetTexture(int id);
	VScene* GetSceneById(int id);

	void SetDirectionalLight(VDirectionalLight* DirectionalLight);

	~VObjectPool();

private:
	int TextureCount;
	std::map<int, VTexture*> Textures;
	int SceneCount;
	std::map<int, VScene*> Scenes;
	int SceneObjectCount;
	std::map<int, VSceneObject*> SceneObjects;
	int ActorComponentCount;
	std::map<int, VActorComponent*> ActorComponents;
};

