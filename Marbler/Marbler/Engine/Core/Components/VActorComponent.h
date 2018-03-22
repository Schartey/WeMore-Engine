#pragma once

#include <string>

class VSceneObject;
class VScene;

class VActorComponent
{
public:
	VActorComponent(VScene* Scene, std::string Name);

	virtual void SetOwner(VSceneObject* Actor);
	virtual void Update(double deltaT);

	virtual void OnInitialize();

	virtual ~VActorComponent();

protected:
	VScene * Scene;
	VSceneObject* Owner;

	std::string Name;
};

