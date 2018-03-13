#include "VMesh.h"


VMesh::VMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, VMaterial* Material)
{
	Vertices = vertices;
	Indices = indices;
	this->Material = Material;

	this->setupMesh();
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

void VMesh::draw()
{
	//Use shading, set textures and lighting information
	Material->Use();
	
	//Set Mesh data in Material
	//glUniformMatrix4fv(glGetUniformLocation(_shader->programHandle, "model"), 1, GL_FALSE, glm::value_ptr(_modelmatrix));
	//glUniformMatrix4fv(glGetUniformLocation(_shader->programHandle, "transform"), 1, GL_FALSE, glm::value_ptr(_transfmatrix));
	//glUniformMatrix4fv(glGetUniformLocation(_shader->programHandle, "ptransform"), 1, GL_FALSE, glm::value_ptr(_parenttransform));
	//glUniformMatrix4fv(glGetUniformLocation(_shader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(GlobalSpace::getActiveObject()->getActiveCamera()->getViewMatrix()));
	//glUniformMatrix4fv(glGetUniformLocation(_shader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(GlobalSpace::getActiveObject()->getActiveCamera()->getProjectionMatrix()));

	//Light and material properties should be set in Material -> where does it get that information from?

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	Material->Release();
	//glBindTexture(GL_TEXTURE_2D, 0);
}

VMesh::~VMesh()
{
}
