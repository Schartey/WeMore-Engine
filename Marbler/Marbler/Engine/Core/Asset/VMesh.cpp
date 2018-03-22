#include "VMesh.h"

#include "../Components/VCameraComponent.h"
#include "../VGame.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

VMesh::VMesh()
{
}

std::vector<Vertex> VMesh::GetVertices()
{
	return Vertices;
}

std::vector<GLuint> VMesh::GetIndices()
{
	return Indices;
}

void VMesh::Setup(std::vector<Vertex> Vertices, std::vector<GLuint> Indices, BBox BoundingBox)
{
	this->Vertices = Vertices;
	this->Indices = Indices;
	this->BoundingBox = BoundingBox;

	this->setupMesh();
}

void VMesh::Setup(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<unsigned int> indices, BBox BoundingBox)
{
	this->_elements = indices.size();
	this->positions = positions;
	this->normals = normals;
	this->uvs = uvs;
	this->indices = indices;
	this->BoundingBox = BoundingBox;

	this->setupMesh();
}

BBox VMesh::GetBoundingBox()
{
	return BoundingBox;
}

void VMesh::setupMesh()
{
	/*glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(Vertex),
		&this->Vertices[0], GL_STATIC_DRAW);


	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(GLuint),
		&this->Indices[0], GL_STATIC_DRAW);


	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, normal));

	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(GLvoid*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	// create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// create positions VBO
	glGenBuffers(1, &VBOPositions);
	glBindBuffer(GL_ARRAY_BUFFER, VBOPositions);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

	// bind positions to location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// create normals VBO
	glGenBuffers(1, &VBONormals);
	glBindBuffer(GL_ARRAY_BUFFER, VBONormals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

	// bind normals to location 1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// create uvs VBO
	glGenBuffers(1, &VBOUVs);
	glBindBuffer(GL_ARRAY_BUFFER, VBOUVs);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);

	// bind uvs to location 3
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// create and bind indices VBO
	glGenBuffers(1, &VBOIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VMesh::RenderPass()
{
	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->_elements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//Material->Release();
}

void VMesh::Draw()
{
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->_elements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

VMesh::~VMesh()
{
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
