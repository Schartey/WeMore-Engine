#pragma once

#include "Objects/VScene.h"
#include "VWindow.h"
#include "Physics/VPhysics.h"
#include "VObjectPool.h"

#include "../GUI/VGUI.h"
#include "../Utils/Configs.h"

#include <vector>
#include <functional>

class VGame
{
public:
	VGame();

	virtual void OnInitialize();
	virtual void Update(double deltaT);
	virtual void RenderPass(VShader* Shader, RenderPassBufferType Type);
	void Draw();
	virtual void QuitGame();

	std::string GetTexturePath();

	std::string GetModelPath();
	Configs* GetConfig();
	VGUI* GetGUI();

	void SetConfig(Configs* config);
	void SetWindow(VWindow* Window);
	void SetPhysics(VPhysics* Physics);
	void SetGUI(VGUI* GUI);

	VObjectPool* GetObjectPool() { return ObjectPool; }
	VWindow* GetWindow() { return Window; }
	VScene* GetActiveScene();
	void SetActiveScene(VScene* Scene);

	VScene* CreateScene(std::string Name);

	std::function<void()> OnQuitDelegate;

	~VGame();

protected:
	Configs * config;
	VWindow * Window;
	VPhysics* Physics;
	VGUI* GUI;
	VObjectPool* ObjectPool;


private:
	VScene * ActiveScene;

	std::vector<VScene*> Scenes;
};

