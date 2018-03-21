#pragma once

#include "VScene.h"
#include "../Asset/VMesh.h"

class VSkybox
{
public:
	VSkybox(VScene* Scene);

	void LoadMesh(std::string filePath);

	glm::vec3 GetScale();
	glm::mat4 GetModelMatrix();
	glm::vec3 GetPosition();

	void SetPosition(glm::vec3 Position);
	void SetRotation(glm::vec3 Rotation);
	void SetScale(glm::vec3 Scale);

	void SetMesh(VMesh* Mesh);
	void SetMaterial(VMaterial* Material);

	virtual void Update();
	void RenderPass(class VShader* Shader);
	void Draw();

	~VSkybox();

private:
	VScene * Scene;
	VMesh* Mesh;
	VMaterial* Material;

	glm::vec3 Position = glm::vec3(1.0f);
	glm::quat Rotation = glm::quat();
	glm::vec3 Scale = glm::vec3(1.0f);

	glm::mat4 ModelMatrix = glm::mat4();
};

