#pragma once

#include "VSceneObject.h"

#include "../Components/VLightComponent.h"

class VPointLight2 : public VSceneObject
{
public:
	VPointLight2(VScene* Scene, std::string Name);

	VLightComponent* GetLightComponent();

	~VPointLight2();
	
private:
	VLightComponent* LightComponent;
};

