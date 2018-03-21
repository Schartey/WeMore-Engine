#include "VSkybox.h"

#include "../../Utils/Assimp/VAssimpUtils.h"

#include "glm/gtx/transform.hpp"

VSkybox::VSkybox(VScene* Scene)
{
	this->Scene = Scene;
}

void VSkybox::LoadMesh(std::string MeshPath)
{
	VAssimpMesh* AssimpMesh = VAssimpUtils::LoadMesh(this->Scene, MeshPath);
	this->SetMesh(AssimpMesh->GetMesh());
	this->SetMaterial(AssimpMesh->GetMaterial());
}

glm::vec3 VSkybox::GetScale()
{
	return Scale;
}

glm::mat4 VSkybox::GetModelMatrix()
{
	return translate(glm::mat4(), this->Position)*glm::toMat4(this->Rotation)*glm::scale(glm::mat4(), this->Scale);
}

glm::vec3 VSkybox::GetPosition()
{
	return Position;
}

void VSkybox::SetPosition(glm::vec3 Position)
{
	this->Position = Position;
}

void VSkybox::SetRotation(glm::vec3 Rotation)
{
	this->Rotation = glm::quat(Rotation);
}

void VSkybox::SetScale(glm::vec3 Scale)
{
	this->Scale = Scale;
}

void VSkybox::SetMesh(VMesh* Mesh)
{
	this->Mesh = Mesh;
}

void VSkybox::SetMaterial(VMaterial* Material)
{
	this->Material = Material;
}

void VSkybox::Update()
{
	ModelMatrix = GetModelMatrix();
}

void VSkybox::RenderPass(VShader* Shader)
{
}

void VSkybox::Draw()
{
}

VSkybox::~VSkybox()
{
}
