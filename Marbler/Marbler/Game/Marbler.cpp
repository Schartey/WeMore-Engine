#include "Marbler.h"

#include "../Engine/Core/Objects/VActor.h"

#include "../Engine/Core/Components/VCameraComponent.h"
#include "../Engine/Core/Components/VMeshComponent.h"
#include "../Engine/Core/Components/VInputComponent.h"
#include "../Engine/Core/Components/VParticleComponent.h"

#include "../Engine/Core/Asset/VTexture.h"
#include "../Engine/Utils/Assimp/VAssimpUtils.h"

#include "../Engine/GUI/Widgets/VTextWidget.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

Marbler::Marbler()
{
}

void Marbler::OnInitialize()
{
	VGame::OnInitialize();

	std::string modelPath = "Models\\";
	std::string texturePath = "Textures\\";

	VScene* MainScene = CreateScene();

	VActor* FloorActor = MainScene->CreateActor("FloorActor");
	FloorActor->bPhysics = true;

	PxRigidStatic* RigidStatic = FloorActor->SetRigidStatic();

	FloorActor->SetPosition(glm::vec3(0.0f, -10.0f, 0.0f));
	FloorActor->SetRotation(glm::vec3(0.0f, 45.0f, 0.0f));
	VMeshComponent* FloorMeshComponent = new VMeshComponent(MainScene, "FloorMeshComponent");

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

	VActor* RailActor = MainScene->CreateActor("RailActor");

	RailActor->bPhysics = true;

	PxRigidStatic* RailActorRigidStatic = RailActor->SetRigidStatic();

	VMeshComponent* Rail1MeshComponent = new VMeshComponent(MainScene, "Rail1MeshComponent");
	Rail1MeshComponent->SetPosition(glm::vec3(19.0f, -5.3f, -1.0f));
	Rail1MeshComponent->SetRotation(glm::vec3(0.0f, 0.0f, 100.0f));

	RailActor->AddComponent(Rail1MeshComponent);

	Rail1MeshComponent->LoadMesh(modelPath + "rail.obj");
	Rail1MeshComponent->GeneratePhysicsShape(GeometryType::Cylinder);
	Rail1MeshComponent->SetBPhysics(true);

	VMeshComponent* Rail2MeshComponent = new VMeshComponent(MainScene, "Rail2MeshComponent");
	Rail2MeshComponent->SetPosition(glm::vec3(19.0f, -5.3f, 1.0f));
	Rail2MeshComponent->SetRotation(glm::vec3(0.0f, 0.0f, 100.0f));

	RailActor->AddComponent(Rail2MeshComponent);

	Rail2MeshComponent->LoadMesh(modelPath + "rail.obj");
	Rail2MeshComponent->GeneratePhysicsShape(GeometryType::Cylinder);
	Rail2MeshComponent->SetBPhysics(true);

	VMeshComponent* Rail3MeshComponent = new VMeshComponent(MainScene, "Rail3MeshComponent");
	Rail3MeshComponent->SetPosition(glm::vec3(38.0f, -16.6f, -1.0f));
	Rail3MeshComponent->SetRotation(glm::vec3(0.0f, 0.0f, 100.0f));

	RailActor->AddComponent(Rail3MeshComponent);

	Rail3MeshComponent->LoadMesh(modelPath + "rail.obj");
	Rail3MeshComponent->GeneratePhysicsShape(GeometryType::Cylinder);
	Rail3MeshComponent->SetBPhysics(true);

	VMeshComponent* Rail4MeshComponent = new VMeshComponent(MainScene, "Rail4MeshComponent");
	Rail4MeshComponent->SetPosition(glm::vec3(38.0f, -16.6f, 1.0f));
	Rail4MeshComponent->SetRotation(glm::vec3(0.0f, 0.0f, 100.0f));

	RailActor->AddComponent(Rail4MeshComponent);

	Rail4MeshComponent->LoadMesh(modelPath + "rail.obj");
	Rail4MeshComponent->GeneratePhysicsShape(GeometryType::Cylinder);
	Rail4MeshComponent->SetBPhysics(true);

	VActor* LandingActor = MainScene->CreateActor("LandingActor");

	LandingActor->bPhysics = true;

	PxRigidStatic* LandingActorRigidStatic = LandingActor->SetRigidStatic();

	VMeshComponent* LandingMeshComponent = new VMeshComponent(MainScene, "LandingMeshComponent");
	LandingMeshComponent->SetPosition(glm::vec3(45.0f, -22.0f, 0.0f));
	LandingMeshComponent->SetScale(glm::vec3(40.0f, 0.1f, 20.0f));

	LandingActor->AddComponent(LandingMeshComponent);

	LandingMeshComponent->LoadMesh(modelPath + "box.fbx");
	LandingMeshComponent->GeneratePhysicsShape(GeometryType::Box);
	LandingMeshComponent->SetBPhysics(true);

	VActor* BoxCrashActor1 = MainScene->CreateActor("BoxCrashActor1");
	BoxCrashActor1->SetPosition(glm::vec3(53.0f, -15.0f, 1.0f));
	BoxCrashActor1->bPhysics = true;

	PxRigidDynamic* BoxCrashRigidDynamic = BoxCrashActor1->SetRigidDynamic();
	BoxCrashRigidDynamic->setMass(0.1f);

	VMeshComponent* BoxCrashMeshComponent1 = new VMeshComponent(MainScene, "BoxCrashMeshComponent1");
	BoxCrashActor1->AddComponent(BoxCrashMeshComponent1);
	BoxCrashMeshComponent1->LoadMesh(modelPath + "box.fbx");
	BoxCrashMeshComponent1->GeneratePhysicsShape(GeometryType::Box);

	VActor* BoxCrashActor2 = MainScene->CreateActor("BoxCrashActor1");
	BoxCrashActor2->SetPosition(glm::vec3(53.0f, -15.0f, 6.0f));
	BoxCrashActor2->bPhysics = true;

	BoxCrashRigidDynamic = BoxCrashActor2->SetRigidDynamic();
	BoxCrashRigidDynamic->setMass(0.1f);

	VMeshComponent* BoxCrashMeshComponent2 = new VMeshComponent(MainScene, "BoxCrashMeshComponent2");
	BoxCrashActor2->AddComponent(BoxCrashMeshComponent2);
	BoxCrashMeshComponent2->LoadMesh(modelPath + "box.fbx");
	BoxCrashMeshComponent2->GeneratePhysicsShape(GeometryType::Box);

	VActor* BoxTestActor = MainScene->CreateActor("BoxTestActor");
	BoxTestActor->SetPosition(glm::vec3(0.0f, 10.0f, 4.0f));
	BoxTestActor->bPhysics = true;

	PxRigidDynamic* RigidDynamic = BoxTestActor->SetRigidDynamic();
	RigidDynamic->setMass(0.1f);

	VMeshComponent* BoxTestMeshComponent = new VMeshComponent(MainScene, "BoxTestMeshComponent");

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
	

	VActor* CameraActor = MainScene->CreateActor("CameraActor");
	//CameraActor->SetPosition(glm::vec3(0.0f, 10.0f, 5.0f));
	CameraActor->bPhysics = true;

	
	VCameraComponent* CameraComponent = new VCameraComponent(MainScene, "CameraComponent");
	CameraActor->AddComponent(CameraComponent);
	CameraComponent->SetProjectionMatrix(90.0f, Window->GetWidth(), Window->GetHeight(), 0.1f, 1000.0f);
	CameraComponent->SetPosition(glm::vec3(0.0f, 5.0f, 20.0f));
	//CameraComponent->SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	//CameraComponent->Rotate(glm::vec3(0.0f, 1.5f, 0.0f));


	PxRigidDynamic* MarbleRigidDynamic = CameraActor->SetRigidDynamic();
	MarbleRigidDynamic->setMass(1.0f);

	VMeshComponent* MarbleComponent = new VMeshComponent(MainScene, "MarbleComponent");
	//MarbleComponent->SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));

	CameraActor->AddComponent(MarbleComponent);

	MarbleComponent->LoadMesh(modelPath + "marble.obj");
	MarbleComponent->GeneratePhysicsShape(GeometryType::Sphere);
	MarbleComponent->SetBPhysics(true);

	//VTexture* MarbleTexture = new VTexture(texturePath + "Lightmap.png");
	//MarbleTexture->Load();
	//MarbleComponent->GetMaterial()->AddLightMapTexture(MarbleTexture);
	VTexture* MarbleTexture = new VTexture(texturePath + "marble_2.jpg");
	MarbleTexture->Load();

	MarbleComponent->GetMaterial()->AddDiffuseTexture(MarbleTexture);
	MarbleComponent->GetMaterial()->SetSpecularColor(glm::vec3(1.0f));
	MarbleComponent->GetMaterial()->SetSpecularIntensity(1.0f);
	MarbleComponent->GetMaterial()->SetSpecularPower(32);

	CameraComponent->SetTarget(MarbleComponent);

	VParticleComponent* MarbleParticleComponent = new VParticleComponent(MainScene, "MarbleParticleComponent");
	VParticleDescriptor* ParticleDescriptor = new VParticleDescriptor();
	ParticleDescriptor->Count = 100000;
	ParticleDescriptor->Position = glm::vec3(0, 0, 0);
	ParticleDescriptor->Spread = 5;
	ParticleDescriptor->TTL = 500;
	ParticleDescriptor->Velocity = glm::vec3(0.1f);

	MarbleParticleComponent->SetParticle(ParticleDescriptor);
	MarbleParticleComponent->SetPosition(glm::vec3(0, 3.0f, 0.0f));

	//Draw it on the floor for now
	FloorActor->AddComponent(MarbleParticleComponent);

	VInputComponent* InputComponent = new VInputComponent(MainScene, "InputComponent");
	CameraActor->AddComponent(InputComponent);

	VDirectionalLight* DirectionalLight = VAssimpUtils::LoadDirectionalLight(modelPath + "box.fbx");
	DirectionalLight->SetAmbient(config->getValue("brightness", "0.0").asFloat());
	DirectionalLight->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	DirectionalLight->SetDiffuse(0.6f);
	DirectionalLight->SetDirection(glm::vec3(0.0f, -1.0f, 0.5f));

	MainScene->SetDirectionalLight(DirectionalLight);

	VPointLight2* PointLight1 = MainScene->CreatePointLight("Pointlight1");
	PointLight1->GetLightComponent()->GetPointLight().Ambient = 0.0f;
	PointLight1->GetLightComponent()->GetPointLight().Diffuse = 0.8f;
	PointLight1->GetLightComponent()->GetPointLight().Color = glm::vec3(1.0f, 1.0f, 1.0f);
	PointLight1->GetLightComponent()->GetPointLight().Attenuation = VAttenuation(0.0f, 0.000001f, 0.1f);

	PointLight1->SetScale(glm::vec3(30.0f));
	PointLight1->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));

	VShader* BaseShader = new VShader("Engine/Shader/base.vert", "Engine/Shader/base.frag");
	FloorMeshComponent->GetMaterial()->SetShader(BaseShader);
	BoxTestMeshComponent->GetMaterial()->SetShader(BaseShader);

	VTextWidget* TextWidget = new VTextWidget();
	TextWidget->GetTextElement()->SetText(Text("Hello World", 340.0f, 570.0f, 0.5f, glm::vec3(1,1,1)));
	GUI->AddWidget(TextWidget);
	//MainScene->AddPointLight(PointLight1);

	MainScene->SetActiveSceneObject(CameraActor);

	this->SetActiveScene(MainScene);
}


Marbler::~Marbler()
{

}
