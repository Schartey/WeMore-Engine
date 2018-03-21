#pragma once

class VActor;
class VScene;

class VActorComponent
{
public:
	VActorComponent(VScene* Scene);

	virtual void SetOwner(VActor* Actor);
	virtual void Update(double deltaT);

	virtual void OnInitialize();

	virtual ~VActorComponent();

protected:
	VScene * Scene;
	VActor* Owner;
};

