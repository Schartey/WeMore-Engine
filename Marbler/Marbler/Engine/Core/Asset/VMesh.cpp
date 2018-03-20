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

BBox VMesh::GetBoundingBox()
{
	return BoundingBox;
}

void VMesh::setupMesh()
{
	glGenVertexArrays(1, &this->VAO);
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
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

glm::mat4 VMesh::GetTranslationMatrix()
{
	return TranslationMatrix;
}

glm::mat4 VMesh::GetScaleMatrix()
{
	return ScaleMatrix;
}

void VMesh::SetTranslationMatrix(glm::mat4 TranslationMatrix)
{
	this->TranslationMatrix = TranslationMatrix;
}

void VMesh::Translate(glm::vec3 TranslationVector)
{
	TranslationMatrix = glm::translate(TranslationMatrix, TranslationVector);
}

void VMesh::Scale(glm::vec3 ScaleVector)
{
	ScaleMatrix = glm::scale(ScaleMatrix, ScaleVector);
}

void VMesh::RenderPass()
{
	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//Material->Release();
}

void VMesh::Draw()
{
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

VMesh::~VMesh()
{
}
