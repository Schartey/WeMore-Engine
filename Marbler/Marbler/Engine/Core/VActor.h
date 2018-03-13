#pragma once

#include "Components/VActorComponent.h"
#include "Components/VSceneComponent.h"

#include <vector>

class VActor
{
public:
	VActor();

	virtual void Update();
	void Draw();

	~VActor();

private:
	std::vector<VActorComponent*> ActorComponents;
	std::vector<VSceneComponent*> SceneComponents;
};

