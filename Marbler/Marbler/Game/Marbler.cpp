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

	RandomActor->ImportMesh("../../Models/", "test.3ds");

	VActor* CameraActor = MainScene->CreateActor();
	CameraActor->Translate(glm::vec3(50.0f, 0.0f, 0.0f));
	
	VCameraComponent* CameraComponent = new VCameraComponent();
	CameraActor->AddComponent(CameraComponent);
	CameraComponent->SetProjectionMatrix(glm::perspective(glm::radians(45.0f), Window->GetWidth() / (float)Window->GetHeight(), 0.1f, 1000.0f));
	CameraComponent->SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

	MainScene->SetActivePlayerActor(CameraActor);

	this->SetActiveScene(MainScene);
}


Marbler::~Marbler()
{
}
