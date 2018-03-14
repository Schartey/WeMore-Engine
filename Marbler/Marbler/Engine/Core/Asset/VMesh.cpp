#include "VMesh.h"

#include "../Components/VCameraComponent.h"
#include "../VGame.h"

#include <glm/gtc/type_ptr.hpp>

VMesh::VMesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, VMaterial* Material, VScene* Scene)
{
	Vertices = vertices;
	Indices = indices;
	this->Material = Material;
	this->Scene = Scene;

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

void VMesh::SetTranslationMatrix(glm::mat4 TranslationMatrix)
{
	this->TranslationMatrix = TranslationMatrix;
}

void VMesh::Draw(glm::mat4 ParentModelMatrix)
{
	//Use shading, set textures and lighting information
	Material->Use();
	VShader* Shader = Material->GetShader();
	
	VCameraComponent* CameraComponent = Scene->GetActivePlayerActor()->GetComponentByClass<VCameraComponent>();
	//Set Mesh data in Material
	glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "translate"), 1, GL_FALSE, glm::value_ptr(TranslationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "rotation"), 1, GL_FALSE, glm::value_ptr(RotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "scale"), 1, GL_FALSE, glm::value_ptr(ScaleMatrix));
	glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "pmodel"), 1, GL_FALSE, glm::value_ptr(ParentModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(Shader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

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
