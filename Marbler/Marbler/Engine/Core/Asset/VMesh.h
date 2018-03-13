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

class VMesh
{
public:
	VMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, VMaterial* material);

	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	VMaterial* Material;

	void draw();
	
	~VMesh();

private:
	GLuint VAO, VBO, EBO;
	glm::mat4 _modelmatrix;

	void setupMesh();
};