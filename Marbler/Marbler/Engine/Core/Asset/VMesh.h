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
	void Setup(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<unsigned int> indices, BBox BoundingBox);
	BBox GetBoundingBox();

	void RenderPass();
	virtual void Draw();
	
	~VMesh();

protected:
	GLuint VAO, VBO, EBO;
	GLuint VBOPositions, VBONormals, VBOUVs, VBOIndices;

	BBox BoundingBox;

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;

	std::vector<glm::vec3> positions;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	unsigned int _elements;

	void setupMesh();
};