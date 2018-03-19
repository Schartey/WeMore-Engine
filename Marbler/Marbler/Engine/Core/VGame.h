#pragma once

#include "VScene.h"
#include "VWindow.h"
#include "Physics/VPhysics.h"

#include <vector>

class VGame
{
public:
	VGame();

	virtual void OnInitialize();
	virtual void Update(double deltaT);
	void RenderPass(VShader* Shader);
	void Draw();
	void SetWindow(VWindow* Window);
	void SetPhysics(VPhysics* Physics);
	VScene* GetActiveScene();

	VScene* CreateScene();

	~VGame();

protected:
	VWindow * Window;
	VPhysics* Physics;

	void SetActiveScene(VScene* Scene);

private:
	VScene * ActiveScene;

	std::vector<VScene*> Scenes;
};

