#include "VSceneObject.h"

#include "../../Utils/Assimp/VAssimpUtils.h"
#include "glm/gtx/transform.hpp"


VSceneObject::VSceneObject(VScene* Scene, std::string Name)
{
	this->Scene = Scene;
	this->Name = Name;
}

void VSceneObject::LoadMesh(std::string MeshPath)
{
	VAssimpMesh* AssimpMesh = VAssimpUtils::LoadMesh(this->Scene, MeshPath);
	this->SetMesh(AssimpMesh->GetMesh());
	this->SetMaterial(AssimpMesh->GetMaterial());
}

glm::vec3 VSceneObject::GetScale()
{
	return Scale;
}

glm::mat4 VSceneObject::GetModelMatrix()
{
 	return translate(glm::mat4(), this->Position)*glm::toMat4(this->Rotation)*glm::scale(glm::mat4(), this->Scale);
}

glm::vec3 VSceneObject::GetPosition()
{
	return Position;
}

glm::quat VSceneObject::GetRotation()
{
	return Rotation;
}

void VSceneObject::SetPosition(glm::vec3 Position)
{
	this->Position = Position;
}

void VSceneObject::SetRotation(glm::vec3 Rotation)
{
	this->Rotation = glm::quat(Rotation);
}

void VSceneObject::SetScale(glm::vec3 Scale)
{
	this->Scale = Scale;
}

void VSceneObject::SetMesh(VMesh* Mesh)
{
	this->Mesh = Mesh;
}

void VSceneObject::SetMaterial(VMaterial* Material)
{
	this->Material = Material;
}

void VSceneObject::Update(double deltaT)
{
	for (VActorComponent* ActorComponent : ActorComponents)
	{
		ActorComponent->Update(deltaT);
	}
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Update(deltaT);
	}
	ModelMatrix = GetModelMatrix();
}

void VSceneObject::RenderPass(VShader* Shader)
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->RenderPass(Shader, ModelMatrix);
	}
}

void VSceneObject::Draw()
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Draw(ModelMatrix);
	}
}

VSceneObject::~VSceneObject()
{
}
