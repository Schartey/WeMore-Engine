#pragma once

#include "Components/VActorComponent.h"
#include "Components/VSceneComponent.h"

#include <vector>

class VScene;

class VActor
{
public:
	VActor(VScene* Scene);

	void ImportMesh(std::string path, std::string filename);

	template <typename T>
	inline T* GetComponentByClass()
	{
		for (VActorComponent* ActorComponent : ActorComponents)
		{
			T* Component = dynamic_cast<T*>(ActorComponent);
			if (Component != nullptr)
			{
				return Component;
			}
		}
		for (VSceneComponent* SceneComponent : SceneComponents)
		{
			T* Component = dynamic_cast<T*>(SceneComponent);
			if (Component != nullptr)
			{
				return Component;
			}
		}
	}

	template <typename T>
	inline void AddComponent(T AddComponent)
	{
		VSceneComponent* SceneComponent = dynamic_cast<VSceneComponent*>(AddComponent);
		if (SceneComponent != nullptr)
		{
			SceneComponents.push_back(SceneComponent);
			return;
		}
		VActorComponent* ActorComponent = dynamic_cast<VActorComponent*>(AddComponent); 
		if (ActorComponent != nullptr)
		{
			ActorComponents.push_back(ActorComponent);
		}
	}

	virtual void Update();
	void Draw();

	~VActor();

private:
	VScene* Scene;
	std::vector<VActorComponent*> ActorComponents;
	std::vector<VSceneComponent*> SceneComponents;
};

