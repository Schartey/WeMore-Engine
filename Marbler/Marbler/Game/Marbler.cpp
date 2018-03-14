#include "Marbler.h"

#include "../Engine/Core/Components/VCameraComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

Marbler::Marbler()
{
}

void Marbler::OnInitialize()
{
	VScene* MainScene = new VScene();

	VActor* RandomActor = MainScene->CreateActor();

	RandomActor->ImportMesh("../../Models/", "Futuristic combat jet.3ds");

	VActor* CameraActor = MainScene->CreateActor();
	
	VCameraComponent* CameraComponent = new VCameraComponent();
	CameraComponent->Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	//CameraComponent->SetProjectionMatrix(glm::perspective(glm::radians(90.0f), Window->GetWidth() / (float)Window->GetHeight(), 0.1f, 1000.0f));
	CameraActor->AddComponent(CameraComponent);

	MainScene->SetActivePlayerActor(CameraActor);

	this->SetActiveScene(MainScene);
}


Marbler::~Marbler()
{
}
