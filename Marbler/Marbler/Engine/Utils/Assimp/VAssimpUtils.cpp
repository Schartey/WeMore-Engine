#include "VAssimpUtils.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/material.h"


VAssimpUtils::VAssimpUtils()
{
}

VAssimpScene* VAssimpUtils::LoadScene(VScene* Scene, std::string path, std::string filename)
{
	std::string filepath;
	filepath.assign(path);
	filepath.append(filename);

	Assimp::Importer import;
	const aiScene* iscene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!iscene || iscene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !iscene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return nullptr;
	}

	VAssimpScene* AssimpScene = new VAssimpScene();

	ProcessScene(Scene, path, AssimpScene, iscene);

	return AssimpScene;
}

void VAssimpUtils::ProcessScene(VScene* Scene, std::string path, VAssimpScene* AssimpScene, const aiScene* iscene)
{

	aiNode* node = iscene->mRootNode;

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(Scene, path, AssimpScene, node->mChildren[i], iscene);
	}
}

void VAssimpUtils::ProcessNode(VScene* Scene, std::string path, VAssimpScene* AssimpScene, const aiNode* Node, const aiScene* iscene)
{
	for (GLuint i = 0; i < Node->mNumMeshes; i++)
	{
		aiMesh* Mesh = iscene->mMeshes[Node->mMeshes[i]];

		VMesh* pMesh = ProcessMesh(Scene, path, AssimpScene, Mesh, Node, iscene);
		AssimpScene->AddMesh(pMesh);
	}
}

VMesh* VAssimpUtils::ProcessMesh(VScene* Scene, std::string path, VAssimpScene* AssimpScene, aiMesh* Mesh, const aiNode* Node, const aiScene* iscene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;


	for (GLuint i = 0; i < Mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// Process vertex positions, normals and texture coordinates
		glm::vec3 vector;
		vector.x = Mesh->mVertices[i].x;
		vector.y = Mesh->mVertices[i].y;
		vector.z = Mesh->mVertices[i].z;
		vertex.position = vector;

		vector.x = Mesh->mNormals[i].x;
		vector.y = Mesh->mNormals[i].y;
		vector.z = Mesh->mNormals[i].z;
		vertex.normal = vector;

		if (Mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = Mesh->mTextureCoords[0][i].x;
			vec.y = Mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
		}
		else
			vertex.texCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}

	// Process indices
	for (GLuint i = 0; i < Mesh->mNumFaces; i++)
	{
		aiFace face = Mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	VMaterial* pMaterial = new VMaterial();

	// Process material
	if (Mesh->mMaterialIndex >= 0)
	{
		aiMaterial* Material = iscene->mMaterials[Mesh->mMaterialIndex];

		pMaterial = ProcessMaterial(path, Material);
	}

	VMesh* pMesh = new VMesh(vertices, indices, pMaterial, Scene);

	pMesh->SetTranslationMatrix(ConvertMat4(Node->mTransformation));

	return pMesh;
}

VMaterial* VAssimpUtils::ProcessMaterial(std::string path, aiMaterial* Material)
{
	VMaterial* pMaterial = new VMaterial();

	for (GLuint i = 0; i < Material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		Material->GetTexture(aiTextureType_DIFFUSE, i, &str);
		VTexture* texture = new VTexture();
		texture->LoadTextureFromFile(str.C_Str(), path);
		pMaterial->AddDiffuseTexture(texture);
	}
	for (GLuint i = 0; i < Material->GetTextureCount(aiTextureType_LIGHTMAP); i++)
	{
		aiString str;
		Material->GetTexture(aiTextureType_LIGHTMAP, i, &str);
		VTexture* texture = new VTexture();
		texture->LoadTextureFromFile(str.C_Str(), path);
		pMaterial->AddLightMapTexture(texture);
	}

	return pMaterial;
}


glm::mat4 VAssimpUtils::ConvertMat4(const aiMatrix4x4 mat)
{
	glm::mat4 nmat;

	nmat[0][0] = mat.a1;
	nmat[0][1] = mat.b1;
	nmat[0][2] = mat.c1;
	nmat[0][3] = mat.d1;
	nmat[1][0] = mat.a2;
	nmat[1][1] = mat.b2;
	nmat[1][2] = mat.c2;
	nmat[1][3] = mat.d2;
	nmat[2][0] = mat.a3;
	nmat[2][1] = mat.b3;
	nmat[2][2] = mat.c3;
	nmat[2][3] = mat.d3;
	nmat[3][0] = mat.a4;
	nmat[3][1] = mat.b4;
	nmat[3][2] = mat.c4;
	nmat[3][3] = mat.d4;

	return nmat;
}

VAssimpUtils::~VAssimpUtils()
{
}
