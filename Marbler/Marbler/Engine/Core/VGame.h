#pragma once

#include "Objects/VScene.h"
#include "VWindow.h"
#include "Physics/VPhysics.h"
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

	void SetConfig(Configs* config);
	void SetWindow(VWindow* Window);
	void SetPhysics(VPhysics* Physics);
	void SetGUI(VGUI* GUI);

	VWindow* GetWindow() { return Window; }
	VScene* GetActiveScene();

	VScene* CreateScene();

	std::function<void()> OnQuitDelegate;

	~VGame();

protected:
	Configs * config;
	VWindow * Window;
	VPhysics* Physics;
	VGUI* GUI;

	void SetActiveScene(VScene* Scene);

private:
	VScene * ActiveScene;

	std::vector<VScene*> Scenes;
};

