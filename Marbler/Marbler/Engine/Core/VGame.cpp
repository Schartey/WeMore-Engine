#include "VGame.h"

#include "Physics/VPhysicsScene.h"
#include "VGameStatics.h"

VGame::VGame()
{
	ObjectPool = new VObjectPool();
}

void VGame::OnInitialize()
{
	VGameStatics::Initialize(this);
}

void VGame::Update(double deltaT)
{
	ActiveScene->Update(deltaT);
}

void VGame::RenderPass(VShader* Shader, RenderPassBufferType Type)
{
	ActiveScene->RenderPass(Shader, Type);
}

void VGame::Draw()
{
	ActiveScene->Draw();
}

void VGame::QuitGame()
{
	OnQuitDelegate();
}

void VGame::ToggleFrustumCulling()
{
	this->frustumCulling = !this->frustumCulling;
}

bool VGame::GetFrustumCulling()
{
	return this->frustumCulling;
}

std::string VGame::GetTexturePath()
{
	return this->config->getValue("textures", "Textures\\").asString();
}

std::string VGame::GetModelPath()
{
	return this->config->getValue("models", "Models\\").asString();
}

Configs* VGame::GetConfig()
{
	return this->config;
}

VGUI* VGame::GetGUI()
{
	return GUI;
}

void VGame::SetConfig(Configs* config)
{
	this->config = config;
}
void VGame::SetWindow(VWindow* Window)
{
	this->Window = Window;
}

void VGame::SetPhysics(VPhysics* Physics)
{
	this->Physics = Physics;
}

void VGame::SetGUI(VGUI* GUI)
{
	this->GUI = GUI;
}

VScene* VGame::GetActiveScene()
{
	return ActiveScene;
}

void VGame::SetActiveScene(VScene* Scene)
{
	ActiveScene = Scene;
}

VScene* VGame::CreateScene(std::string Name)
{
	VScene* Scene = new VScene(Name);
	return Scene;
}

VGame::~VGame()
{
}
