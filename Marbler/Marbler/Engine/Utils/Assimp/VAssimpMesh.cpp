#include "VAssimpMesh.h"
#include <glm/gtx/matrix_decompose.hpp>

VAssimpMesh::VAssimpMesh(VMesh* Mesh, VMaterial* Material, glm::mat4 Transform)
{
	this->Mesh = Mesh;
	this->Material = Material;
	glm::vec3 Skew;
	glm::vec4 Perspective;

	glm::decompose(Transform, this->Scale, this->Rotation, this->Position, Skew, Perspective);
	this->Rotation = glm::conjugate(this->Rotation);
}

VMesh* VAssimpMesh::GetMesh()
{
	return Mesh;
}

VMaterial* VAssimpMesh::GetMaterial()
{
	return Material;
}

glm::vec3 VAssimpMesh::GetPosition()
{
	return Position;
}

glm::quat VAssimpMesh::GetRotation()
{
	return Rotation;
}

glm::vec3 VAssimpMesh::GetScale()
{
	return Scale;
}

VAssimpMesh::~VAssimpMesh()
{
}
