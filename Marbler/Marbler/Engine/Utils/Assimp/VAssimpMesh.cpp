#include "VAssimpMesh.h"



VAssimpMesh::VAssimpMesh(VMesh* Mesh, VMaterial* Material, glm::mat4 Transform)
{
	this->Mesh = Mesh;
	this->Material = Material;
	this->Transformation = Transform;
}

VMesh* VAssimpMesh::GetMesh()
{
	return Mesh;
}

VMaterial* VAssimpMesh::GetMaterial()
{
	return Material;
}

glm::mat4 VAssimpMesh::GetTransformation()
{
	return Transformation;
}

VAssimpMesh::~VAssimpMesh()
{
}
