#pragma once

#include "Components/VActorComponent.h"
#include "Components/VSceneComponent.h"

#include <vector>

#include "Physics/VPhysicsActor.h"

class VScene;

class VActor
{
public:
	VActor(VScene* Scene);

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

	void SetupBasicRigidBody();

	void AddPhysicsShape(VPhysicsShape* PhysicsShape);

	void Translate(glm::vec3 vector);

	glm::mat4 GetModelMatrix();
	glm::mat4 GetTransformationMatrix();
	void SetTransformationMatrix(glm::mat4 TransformationMatrix);

	virtual void Update();
	void RenderPass(class VShader* Shader);
	void Draw();

	~VActor();

private:
	VScene* Scene;
	VPhysicsActor* PhysicsActor;

	std::vector<VActorComponent*> ActorComponents;
	std::vector<VSceneComponent*> SceneComponents;

	glm::mat4 ModelMatrix = glm::mat4();
	glm::mat4 TranslationMatrix = glm::mat4();
	glm::mat4 RotationMatrix = glm::mat4();
	glm::mat4 ScaleMatrix = glm::mat4();

	glm::mat4 TransformationMatrix = glm::mat4();
};

