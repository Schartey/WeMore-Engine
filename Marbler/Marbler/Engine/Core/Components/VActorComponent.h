#pragma once

class VActor;
class VScene;

class VActorComponent
{
public:
	VActorComponent(VScene* Scene);

	virtual void SetOwner(VActor* Actor);
	virtual void Update();

	virtual void OnInitialize();

	virtual ~VActorComponent();

protected:
	VScene * Scene;
	VActor* Owner;
};

