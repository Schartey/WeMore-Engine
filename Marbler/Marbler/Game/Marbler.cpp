#include "Marbler.h"

#include "../Engine/Core/Components/VCameraComponent.h"
#include "../Engine/Core/Components/VMeshComponent.h"
#include "../Engine/Core/Components/VInputComponent.h"

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
	std::string modelPath = "..\\..\\Models\\";
	std::string texturePath = "..\\..\\Textures\\";

	VScene* MainScene = CreateScene();

	
	VActor* FloorActor = MainScene->CreateActor();
	FloorActor->bPhysics = true;

	PxRigidStatic* RigidStatic = FloorActor->SetRigidStatic();

	FloorActor->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	VMeshComponent* FloorMeshComponent = new VMeshComponent(MainScene);

	FloorActor->AddComponent(FloorMeshComponent);
	
	FloorMeshComponent->LoadMesh(modelPath + "box.fbx");
	FloorMeshComponent->GeneratePhysicsShape(GeometryType::Box);
	FloorMeshComponent->SetBPhysics(true);

	FloorMeshComponent->SetScale(glm::vec3(10.0f, 0.1f, 10.0f));

	VTexture* FloorTexture = new VTexture(texturePath + "Lightmap.png");
	FloorTexture->Load();
	FloorMeshComponent->GetMaterial()->AddLightMapTexture(FloorTexture);
	FloorMeshComponent->GetMaterial()->SetSpecularColor(glm::vec3(1.0f));
	FloorMeshComponent->GetMaterial()->SetSpecularIntensity(1.0f);
	FloorMeshComponent->GetMaterial()->SetSpecularPower(1);
	

	VActor* BoxTestActor = MainScene->CreateActor();
	BoxTestActor->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));
	BoxTestActor->bPhysics = true;

	PxRigidDynamic* RigidDynamic = BoxTestActor->SetRigidDynamic();
	RigidDynamic->setMass(0.1f);

	VMeshComponent* BoxTestMeshComponent = new VMeshComponent(MainScene);

	BoxTestActor->AddComponent(BoxTestMeshComponent);

	BoxTestMeshComponent->LoadMesh(modelPath + "box.fbx");
	BoxTestMeshComponent->GeneratePhysicsShape(GeometryType::Box);

	VTexture* BoxTestTexture = new VTexture(texturePath + "Lightmap.png");
	BoxTestTexture->Load();
	BoxTestMeshComponent->GetMaterial()->AddLightMapTexture(BoxTestTexture);
	BoxTestMeshComponent->GetMaterial()->SetSpecularColor(glm::vec3(1.0f));
	BoxTestMeshComponent->GetMaterial()->SetSpecularIntensity(1.0f);
	BoxTestMeshComponent->GetMaterial()->SetSpecularPower(1);
	
	/*VMesh* Mesh = VAssimpUtils::LoadMesh(MainScene, modelPath, "box.fbx");
	VTexture* texture = new VTexture();
	texture->LoadTextureFromFile(texturePath + "/Lightmap.png");
	Mesh->GetMaterial()->AddLightMapTexture(texture);
	Mesh->GetMaterial()->SetSpecularColor(glm::vec3(1.0f));
	Mesh->GetMaterial()->SetSpecularIntensity(0.5f);
	Mesh->GetMaterial()->SetSpecularPower(32);

	VMeshComponent* MeshComponent = new VMeshComponent();
	MeshComponent->SetMesh(Mesh);

	VActor* RandomActor = MainScene->CreateActor();

	RandomActor->AddComponent(MeshComponent);*/

	//VActor* MarbleActor = MainScene->CreateActor();
	//MarbleActor->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));
	

	VActor* CameraActor = MainScene->CreateActor();
	CameraActor->SetPosition(glm::vec3(0.0f, 10.0f, 5.0f));
	CameraActor->bPhysics = true;

	
	VCameraComponent* CameraComponent = new VCameraComponent(MainScene);
	CameraActor->AddComponent(CameraComponent);
	CameraComponent->SetProjectionMatrix(glm::perspective(glm::radians(90.0f), Window->GetWidth() / (float)Window->GetHeight(), 0.1f, 1000.0f));
	CameraComponent->SetPosition(glm::vec3(0.0f, 5.0f, 20.0f));
	//CameraComponent->SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	//CameraComponent->Rotate(glm::vec3(0.0f, 1.5f, 0.0f));


	PxRigidDynamic* MarbleRigidDynamic = CameraActor->SetRigidDynamic();
	MarbleRigidDynamic->setMass(1.0f);

	VMeshComponent* MarbleComponent = new VMeshComponent(MainScene);

	CameraActor->AddComponent(MarbleComponent);

	MarbleComponent->LoadMesh(modelPath + "marble.fbx");
	MarbleComponent->GeneratePhysicsShape(GeometryType::Sphere);
	//MarbleComponent->SetBPhysics(true);

	//VTexture* MarbleTexture = new VTexture(texturePath + "Lightmap.png");
	//MarbleTexture->Load();
	//MarbleComponent->GetMaterial()->AddLightMapTexture(MarbleTexture);
	MarbleComponent->GetMaterial()->SetSpecularColor(glm::vec3(1.0f));
	MarbleComponent->GetMaterial()->SetSpecularIntensity(1.0f);
	MarbleComponent->GetMaterial()->SetSpecularPower(1);


	VInputComponent* InputComponent = new VInputComponent(MainScene);
	CameraActor->AddComponent(InputComponent);

	VDirectionalLight* DirectionalLight = VAssimpUtils::LoadDirectionalLight(modelPath + "box.fbx");
	DirectionalLight->SetAmbient(0.1f);
	DirectionalLight->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	DirectionalLight->SetDiffuse(0.5f);
	DirectionalLight->SetDirection(glm::vec3(0.0f, -1.0f, 0.5f));

	MainScene->SetDirectionalLight(DirectionalLight);

	VPointLight* PointLight1 = VAssimpUtils::LoadPointLight(modelPath + "sphere.obj");
	PointLight1->SetAmbient(0.5f);
	PointLight1->SetDiffuse(0.5f);
	PointLight1->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	PointLight1->SetTranslationMatrix(glm::mat4());
	PointLight1->Translate(glm::vec3(3.0f, -3.0f, -1.0f));
	PointLight1->SetAttenuation(VAttenuation(0.0f, 0.0f, 0.3f));
	PointLight1->Scale(glm::vec3(5.0f));

	VShader* BaseShader = new VShader("Engine/Shader/base.vert", "Engine/Shader/base.frag");
	FloorMeshComponent->GetMaterial()->SetShader(BaseShader);
	BoxTestMeshComponent->GetMaterial()->SetShader(BaseShader);

	MainScene->AddPointLight(PointLight1);

	MainScene->SetActivePlayerActor(CameraActor);

	this->SetActiveScene(MainScene);
}


Marbler::~Marbler()
{
}
