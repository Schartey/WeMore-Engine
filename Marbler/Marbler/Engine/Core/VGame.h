#pragma once

#include "VScene.h"
#include "VWindow.h"

#include <vector>

class VGame
{
public:
	VGame();

	virtual void OnInitialize();
	virtual void Update();
	virtual void Draw();
	void SetWindow(VWindow* Window);

	~VGame();

protected:
	VWindow* Window;

	void SetActiveScene(VScene* Scene);

private:
	VScene * ActiveScene;

	std::vector<VScene*> Scenes;
};

