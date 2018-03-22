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
	filepath.append("/");
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

VAssimpMesh* VAssimpUtils::LoadMesh(VScene* Scene, std::string filePath)
{
	Assimp::Importer import;
	const aiScene* iscene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!iscene || iscene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !iscene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return nullptr;
	}

	std::string directoryPath = filePath.substr(0, filePath.find_last_of('\\')+1);

	VAssimpScene* AssimpScene = new VAssimpScene();

	ProcessScene(Scene, directoryPath, AssimpScene, iscene);

	return AssimpScene->GetMeshes().size() > 0 ? AssimpScene->GetMeshes().at(0) : nullptr;
}

/*VPointLight* VAssimpUtils::LoadPointLight(std::string filePath)
{
	VAssimpMesh* Mesh = LoadMesh(nullptr, filePath);
	VPointLight* Light = new VPointLight();
	Light->Setup(Mesh->GetMesh()->GetVertices(), Mesh->GetMesh()->GetIndices(), Mesh->GetMesh()->GetBoundingBox());

	return Light;
}*/

VDirectionalLight* VAssimpUtils::LoadDirectionalLight(std::string filePath)
{
	VAssimpMesh* Mesh = LoadMesh(nullptr, filePath);
	VDirectionalLight* Light = new VDirectionalLight();
	Light->Setup(Mesh->GetMesh()->GetVertices(), Mesh->GetMesh()->GetIndices(), Mesh->GetMesh()->GetBoundingBox());

	return Light;
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

		VAssimpMesh* AssimpMesh = ProcessMesh(Scene, path, AssimpScene, Mesh, Node, iscene);
		AssimpScene->AddMesh(AssimpMesh);
	}
}

VAssimpMesh* VAssimpUtils::ProcessMesh(VScene* Scene, std::string path, VAssimpScene* AssimpScene, aiMesh* Mesh, const aiNode* Node, const aiScene* iscene)
{
	std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned int> indices;

	//std::vector<GLuint> indices;

	BBox BoundingBox;
	BoundingBox.min.x = BoundingBox.max.x = Mesh->mVertices[0].x;
	BoundingBox.min.y = BoundingBox.max.y = Mesh->mVertices[0].y;
	BoundingBox.min.z = BoundingBox.max.z = Mesh->mVertices[0].z;

	for (GLuint i = 0; i < Mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// Process vertex positions, normals and texture coordinates
		glm::vec3 vector;
		vector.x = Mesh->mVertices[i].x;
		vector.y = Mesh->mVertices[i].y;
		vector.z = Mesh->mVertices[i].z;
		vertex.position = vector;
		positions.push_back(vector);

		vector.x = Mesh->mNormals[i].x;
		vector.y = Mesh->mNormals[i].y;
		vector.z = Mesh->mNormals[i].z;
		vertex.normal = vector;
		normals.push_back(vector);

		if (Mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = Mesh->mTextureCoords[0][i].x;
			vec.y = Mesh->mTextureCoords[0][i].y;
			vertex.texCoords = vec;
			uvs.push_back(vec);
		}
		else
			uvs.push_back(glm::vec2(0.0f, 0.0f));

		//Calculate Bounding Box
		if (Mesh->mVertices[i].x < BoundingBox.min.x) BoundingBox.min.x = Mesh->mVertices[i].x;
		if (Mesh->mVertices[i].x > BoundingBox.max.x) BoundingBox.max.x = Mesh->mVertices[i].x;
		if (Mesh->mVertices[i].y < BoundingBox.min.y) BoundingBox.min.y = Mesh->mVertices[i].y;
		if (Mesh->mVertices[i].y > BoundingBox.max.y) BoundingBox.max.y = Mesh->mVertices[i].y;
		if (Mesh->mVertices[i].z < BoundingBox.min.z) BoundingBox.min.z = Mesh->mVertices[i].z;
		if (Mesh->mVertices[i].z > BoundingBox.max.z) BoundingBox.max.z = Mesh->mVertices[i].z;

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

	VMesh* pMesh = new VMesh();

	//pMesh->Setup(vertices, indices, BoundingBox);
	pMesh->Setup(positions, normals, uvs, indices, BoundingBox);

	VAssimpMesh* AssimpMesh = new VAssimpMesh(pMesh, pMaterial, ConvertMat4(Node->mTransformation));

	return AssimpMesh;
}

VMaterial* VAssimpUtils::ProcessMaterial(std::string path, aiMaterial* Material)
{
	VMaterial* pMaterial = new VMaterial();

	for (GLuint i = 0; i < Material->GetTextureCount(aiTextureType_DIFFUSE); i++)
	{
		aiString str;
		Material->GetTexture(aiTextureType_DIFFUSE, i, &str);
		std::string name = str.C_Str();
		std::string filePath = path.append(str.C_Str());

		VTexture* texture = new VTexture(filePath.c_str());
		texture->Load();

		pMaterial->AddDiffuseTexture(texture);
	}

	glm::vec3 color;
	Material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	pMaterial->SetDiffuse(color);
	Material->Get(AI_MATKEY_COLOR_SPECULAR, color);
	pMaterial->SetSpecularColor(color);
	float SpecularIntensity;
	Material->Get(AI_MATKEY_SHININESS, SpecularIntensity);
	pMaterial->SetSpecularIntensity(SpecularIntensity);
	Material->Get(AI_MATKEY_SHININESS_STRENGTH, SpecularIntensity);
	pMaterial->SetSpecularPower(SpecularIntensity);

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
