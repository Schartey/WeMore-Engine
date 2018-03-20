#include "VScene.h"

VScene::VScene()
{
	// setup default scene
	PhysicsScene = VPhysics::GetInstance()->CreateDefaultScene();
}

VActor* VScene::CreateActor()
{
	VActor* Actor = new VActor(this);

	Actors.push_back(Actor);

	return Actor;
}

VPointLight* VScene::CreatePointLight()
{
	VPointLight* PointLight = new VPointLight();
	return PointLight;
}

VDirectionalLight* VScene::CreateDirectionalLight()
{
	VDirectionalLight* DirectionalLight = new VDirectionalLight();
	return DirectionalLight;
}

void VScene::AddPointLight(VPointLight* PointLight)
{
	PointLights.push_back(PointLight);
}

void VScene::SetDirectionalLight(VDirectionalLight* DirectionalLight)
{
	this->DirectionalLight = DirectionalLight;
}

std::vector<VPointLight*> VScene::GetPointLights()
{
	return PointLights;
}

VDirectionalLight* VScene::GetDirectionalLight()
{
	return DirectionalLight;
}

PxScene* VScene::GetPhysicsScene()
{
	return PhysicsScene;
}

VActor* VScene::GetActivePlayerActor()
{
	return ActivePlayerActor;
}

void VScene::SetActivePlayerActor(VActor* Actor)
{
	this->ActivePlayerActor = Actor;
}

void VScene::Update()
{
	for (VActor* Actor : Actors)
	{
		Actor->Update();
	}
}

void VScene::RenderPass(VShader* Shader)
{
	for (VActor* Actor : Actors)
	{
		Actor->RenderPass(Shader);
	}
}

void VScene::Draw()
{
	for (VActor* Actor : Actors)
	{
		Actor->Draw();
	}
}

VScene::~VScene()
{
}
