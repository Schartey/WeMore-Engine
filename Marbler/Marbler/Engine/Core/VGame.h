#pragma once

#include "Objects/VScene.h"
#include "VWindow.h"
#include "Physics/VPhysics.h"

#include <vector>
#include <functional>

class VGame
{
public:
	VGame();

	virtual void OnInitialize();
	virtual void Update(double deltaT);
	void RenderPass(VShader* Shader, RenderPassBufferType Type);
	void Draw();
	virtual void QuitGame();

	void SetWindow(VWindow* Window);
	void SetPhysics(VPhysics* Physics);
	VScene* GetActiveScene();

	VScene* CreateScene();

	std::function<void()> OnQuitDelegate;

	~VGame();

protected:
	VWindow * Window;
	VPhysics* Physics;

	void SetActiveScene(VScene* Scene);

private:
	VScene * ActiveScene;

	std::vector<VScene*> Scenes;
};

