#pragma once

#include "VScene.h"
#include "VWindow.h"

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
	VScene* GetActiveScene();

	~VGame();

protected:
	VWindow* Window;

	void SetActiveScene(VScene* Scene);

private:
	VScene * ActiveScene;

	std::vector<VScene*> Scenes;
};

