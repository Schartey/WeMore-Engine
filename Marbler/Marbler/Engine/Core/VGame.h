#pragma once

#include "VScene.h"

#include <vector>

class VGame
{
public:
	VGame();

	virtual void Update();
	void Draw();

	~VGame();

private:
	VScene * ActiveScene;

	std::vector<VScene*> Scenes;

};

