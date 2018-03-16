#include "Marbler.h"

#include "../Engine/Core/Components/VCameraComponent.h"
#include "../Engine/Core/Components/VMeshComponent.h"
#include "../Engine/Core/Asset/VTexture.h"
#include "../Engine/Utils/Assimp/VAssimpUtils.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

Marbler::Marbler()
{
}

void Marbler::OnInitialize()
{
	std::string modelPath = "../../Models";
	std::string texturePath = "../../Textures";

	VScene* MainScene = new VScene();

	VActor* RandomActor = MainScene->CreateActor();

	VMesh* Mesh = VAssimpUtils::LoadMesh(MainScene, modelPath, "box.fbx");
	VTexture* texture = new VTexture();
	texture->LoadTextureFromFile(texturePath + "/Lightmap.png");
	Mesh->GetMaterial()->AddLightMapTexture(texture);

	VMeshComponent* MeshComponent = new VMeshComponent();
	MeshComponent->SetMesh(Mesh);
	RandomActor->AddComponent(MeshComponent);


	VActor* FloorActor = MainScene->CreateActor();

	Mesh = VAssimpUtils::LoadMesh(MainScene, modelPath, "box.fbx");
	texture = new VTexture();
	texture->LoadTextureFromFile(texturePath + "/Lightmap.png");
	Mesh->GetMaterial()->AddLightMapTexture(texture);
	Mesh->Scale(glm::vec3(10.0f, 10.0f, 0.1f));
	Mesh->Translate(glm::vec3(0.0f, 0.0f, -2.0f));

	MeshComponent = new VMeshComponent();
	MeshComponent->SetMesh(Mesh);
	FloorActor->AddComponent(MeshComponent);
	

	VActor* CameraActor = MainScene->CreateActor();
	CameraActor->Translate(glm::vec3(-20.0f, 10.0f, -10.0f));
	
	VCameraComponent* CameraComponent = new VCameraComponent();
	CameraActor->AddComponent(CameraComponent);
	CameraComponent->SetProjectionMatrix(glm::perspective(glm::radians(45.0f), Window->GetWidth() / (float)Window->GetHeight(), 0.1f, 1000.0f));
	CameraComponent->SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

	VDirectionalLight* DirectionalLight = VAssimpUtils::LoadDirectionalLight(modelPath, "box.fbx");
	DirectionalLight->SetAmbient(0.1f);
	DirectionalLight->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	DirectionalLight->SetDiffuse(0.5f);
	DirectionalLight->SetDirection(glm::vec3(0.0f, 1.0f, 0.0f));

	MainScene->SetDirectionalLight(DirectionalLight);

	VPointLight* PointLight1 = VAssimpUtils::LoadPointLight(modelPath, "sphere.obj");
	PointLight1->SetAmbient(0.5f);
	PointLight1->SetDiffuse(0.5f);
	PointLight1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	PointLight1->SetTranslationMatrix(glm::mat4());
	PointLight1->Translate(glm::vec3(-1.0f));
	PointLight1->SetAttenuation(VAttenuation(0.0f, 0.0f, 0.5f));
	PointLight1->Scale(glm::vec3(9.0f));

	//MainScene->AddPointLight(PointLight1);

	MainScene->SetActivePlayerActor(CameraActor);

	this->SetActiveScene(MainScene);
}


Marbler::~Marbler()
{
}
