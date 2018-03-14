#pragma once

#include "VActor.h"

#include <vector>

class VScene
{
public:
	VScene();

	VActor* CreateActor();
	VActor* GetActivePlayerActor();
	void SetActivePlayerActor(VActor* Actor);

	virtual void Update();
	void Draw();

	~VScene();

private:
	VActor * ActivePlayerActor;
	
	std::vector<VActor*> Actors;
};

