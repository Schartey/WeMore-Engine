#pragma once

#include "../Asset/VMesh.h"

#include "../Components/VActorComponent.h"
#include "../Components/VSceneComponent.h"

class VScene;

class VSceneObject
{
public:
	VSceneObject(VScene* Scene, std::string Name);

	virtual void LoadMesh(std::string filePath);

	glm::vec3 GetScale();
	glm::mat4 GetModelMatrix();
	glm::vec3 GetPosition();
	glm::quat GetRotation();
	std::string GetName();

	virtual void SetPosition(glm::vec3 Position);
	virtual void SetRotationDeg(glm::vec3 Rotation);
	void SetRotation(glm::quat Rotation);
	void SetScale(glm::vec3 Scale);

	void SetMesh(VMesh* Mesh);
	void SetMaterial(VMaterial* Material);

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

	virtual void Update(double deltaT);
	virtual void RenderPass(class VShader* Shader, RenderPassBufferType Type);
	void Draw();

	~VSceneObject();

protected:
	VScene * Scene;
	VMesh* Mesh;
	VMaterial* Material;

	glm::vec3 Position = glm::vec3(1.0f);
	glm::quat Rotation = glm::quat();
	glm::vec3 Scale = glm::vec3(1.0f);

	glm::mat4 ModelMatrix = glm::mat4();

	std::vector<VActorComponent*> ActorComponents;
	std::vector<VSceneComponent*> SceneComponents;

	std::string Name;
};

