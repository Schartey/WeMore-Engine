#pragma once

#include "VActor.h"

#include <vector>

class VScene
{
public:
	VScene();

	virtual void Update();
	void Draw();

	~VScene();

private:
	std::vector<VActor*> Actors;
};

