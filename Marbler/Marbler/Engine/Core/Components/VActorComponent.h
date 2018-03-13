#pragma once

class VActor;

class VActorComponent
{
public:
	VActorComponent();

	void SetOwner(VActor* Actor);

	virtual void Update();

	~VActorComponent();

private:
	VActor* Owner;
};

