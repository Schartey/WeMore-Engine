#include "VActor.h"

#include "../Utils/Assimp/VAssimpUtils.h"
#include "Components/VMeshComponent.h"

VActor::VActor(VScene* Scene)
{
	this->Scene = Scene;
}

void VActor::ImportMesh(std::string path, std::string filename)
{
	VAssimpScene* AssimpScene = VAssimpUtils::LoadScene(Scene, path, filename);
	
	if (AssimpScene != nullptr)
	{
		std::vector<VMesh*> Meshes = AssimpScene->GetMeshes();

		for (VMesh* Mesh : Meshes)
		{
			VMeshComponent* MeshComponent = new VMeshComponent();
			MeshComponent->SetMesh(Mesh);
			MeshComponent->SetOwner(this);

			this->SceneComponents.push_back((VSceneComponent*)MeshComponent);
		}
	}
	else 
	{
		std::cout << "Loading Mesh failed" << std::endl;
	}
}

void VActor::Update()
{
	for (VActorComponent* ActorComponent : ActorComponents)
	{
		ActorComponent->Update();
	}
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Update();
	}
}

void VActor::Draw()
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Draw();
	}
}


VActor::~VActor()
{
}
