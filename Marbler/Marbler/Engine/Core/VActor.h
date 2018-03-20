#pragma once

#include "Components/VActorComponent.h"
#include "Components/VSceneComponent.h"

#include <vector>

#include "Physics/VPhysics.h"

#include "glm/gtc/quaternion.hpp"

class VScene;

class VActor
{
public:
	VActor(VScene* Scene);

	bool bPhysics = false;

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
		return nullptr;
	}

	template <typename T>
	inline void AddComponent(T AddComponent)
	{
		VSceneComponent* SceneComponent = dynamic_cast<VSceneComponent*>(AddComponent);
		if (SceneComponent != nullptr)
		{
			SceneComponent->SetOwner(this);
			SceneComponent->OnInitialize();
			SceneComponents.push_back(SceneComponent);
			return;
		}
		VActorComponent* ActorComponent = dynamic_cast<VActorComponent*>(AddComponent); 
		if (ActorComponent != nullptr)
		{
			ActorComponent->SetOwner(this);
			ActorComponent->OnInitialize();
			ActorComponents.push_back(ActorComponent);
		}
	}
	
	glm::vec3 GetScale();
	glm::mat4 GetModelMatrix();
	glm::vec3 GetPosition();

	template <typename T>
	inline T* GetRigidActor()
	{
		T* Actor =  dynamic_cast<T*>(RigidActor);

		if (Actor != nullptr)
			return Actor;
		return nullptr;

	}

	void SetPosition(glm::vec3 Position);
	void SetRotation(glm::vec3 Rotation);
	void SetScale(glm::vec3 Scale);
	PxRigidDynamic* SetRigidDynamic();
	PxRigidStatic* SetRigidStatic();

	virtual void Update();
	void RenderPass(class VShader* Shader);
	void Draw();

	~VActor();

private:
	VScene* Scene;
	PxRigidActor* RigidActor;

	glm::vec3 Position = glm::vec3(1.0f);
	glm::quat Rotation = glm::quat();
	glm::vec3 Scale = glm::vec3(1.0f);

	glm::mat4 ModelMatrix = glm::mat4();

	std::vector<VActorComponent*> ActorComponents;
	std::vector<VSceneComponent*> SceneComponents;
};

