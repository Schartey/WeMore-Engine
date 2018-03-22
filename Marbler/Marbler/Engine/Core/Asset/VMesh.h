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

	void RenderPass();
	virtual void Draw();
	
	~VMesh();

protected:
	GLuint VAO, VBO, EBO;

	BBox BoundingBox;

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;

	void setupMesh();
};