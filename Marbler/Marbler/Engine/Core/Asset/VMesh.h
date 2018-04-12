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

	Vertex() { }
	Vertex(glm::vec3 Position, glm::vec3 Normal, glm::vec2 TexCoords)
	{
		this->position = Position;
		this->normal = Normal;
		this->texCoords = TexCoords;
	}
};

struct BBox
{
	glm::vec3 min;
	glm::vec3 max;

	BBox() { }

	BBox(glm::vec3 Min, glm::vec3 Max)
	{
		this->min = Min;
		this->max = Max;
	}
};

class VScene;

class VMesh
{
public:
	VMesh();

	std::vector<Vertex> GetVertices();
	std::vector<int> GetIndices();

	void Setup(std::vector<Vertex> vertices, std::vector<int> indices, BBox BoundingBox);
	BBox GetBoundingBox();

	void RenderPass();
	virtual void Draw();
	
	~VMesh();

protected:
	GLuint VAO, VBO, EBO;

	BBox BoundingBox;

	std::vector<Vertex> Vertices;
	std::vector<int> Indices;

	void setupMesh();
};