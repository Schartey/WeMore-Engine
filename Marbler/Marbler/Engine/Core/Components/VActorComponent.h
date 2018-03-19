#pragma once

class VActor;

class VActorComponent
{
public:
	VActorComponent();

	virtual void SetOwner(VActor* Actor);
	virtual void Update();

	virtual void OnInitialize();

	virtual ~VActorComponent();

protected:
	VActor* Owner;
};

