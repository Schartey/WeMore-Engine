#pragma once

#include <vector>

#include <GL\glew.h>

#include <glm/glm.hpp>

#include "VMaterial.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct BBox
{
	glm::vec3 min;
	glm::vec3 max;
};

class VScene;

class VMesh
{
public:
	VMesh();

	std::vector<Vertex> GetVertices();
	std::vector<GLuint> GetIndices();

	void Setup(std::vector<Vertex> vertices, std::vector<GLuint> indices, BBox BoundingBox);
	BBox GetBoundingBox();

	glm::mat4 GetTranslationMatrix();
	glm::mat4 GetScaleMatrix();

	void SetTranslationMatrix(glm::mat4 TranslationMatrix);

	void Translate(glm::vec3 TranslationVector);
	void Scale(glm::vec3 ScaleVector);

	void RenderPass();
	virtual void Draw(glm::mat4 ParentModelMatrix);
	
	~VMesh();

protected:
	GLuint VAO, VBO, EBO;
	glm::mat4 TranslationMatrix = glm::mat4();
	glm::mat4 RotationMatrix = glm::mat4();
	glm::mat4 ScaleMatrix = glm::mat4();

	BBox BoundingBox;

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;

	void setupMesh();
};