#include "VPointLight2.h"

VPointLight2::VPointLight2(VScene* Scene, std::string Name) : VSceneObject(Scene, Name)
{
	LightComponent = new VLightComponent(Scene, Name.append("-LightComponent"), LightType::PointLight);
	LightComponent->SetOwner(this);
	this->SceneComponents.push_back(LightComponent);
}

VLightComponent* VPointLight2::GetLightComponent()
{
	return LightComponent;
}

VPointLight2::~VPointLight2()
{
}
