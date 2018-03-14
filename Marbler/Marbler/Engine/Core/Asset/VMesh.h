#pragma once

#include <vector>

#include <GL\glew.h>

#include <glm/glm.hpp>

#include "VMaterial.h"
#include "../VScene.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class SceneComponent;

class VMesh
{
public:
	VMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, VMaterial* material, VScene* Scene);

	void SetTranslationMatrix(glm::mat4 TranslationMatrix);

	void Draw(glm::mat4 ParentModelMatrix);
	
	~VMesh();

private:
	GLuint VAO, VBO, EBO;
	glm::mat4 TranslationMatrix = glm::mat4();
	glm::mat4 RotationMatrix = glm::mat4();
	glm::mat4 ScaleMatrix = glm::mat4();

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;

	VMaterial* Material;
	VScene* Scene;

	void setupMesh();
};