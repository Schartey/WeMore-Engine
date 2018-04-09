#include "VLightComponent.h"

#include "../Objects/VSceneObject.h"

VLightComponent::VLightComponent(VScene* Scene, std::string Name, LightType lightType) : VMeshComponent(Scene, Name)
{
	this->lightType = lightType;

	switch (this->lightType)
	{
	case LightType::PointLight:
		LoadMesh("..\\..\\Models\\sphere.obj");
	}
}

glm::vec3 VLightComponent::GetGlobalPosition()
{
	return this->Position + this->Owner->GetPosition();
}

glm::vec3 VLightComponent::GetGlobalScale()
{
	return this->Scale + this->Owner->GetScale();
}

LightType VLightComponent::GetLightType()
{
	return lightType;
}
VPointLight& VLightComponent::GetPointLight()
{
	return this->PointLight;
}

void VLightComponent::RenderPass(VShader* Shader, glm::mat4 ParentMatrix)
{
	//VMeshComponent::RenderPass(Shader, ParentMatrix);
	//this->Mesh->RenderPass();
}

void VLightComponent::LightRenderPass()
{
	if (this->Mesh != nullptr)
	{
		Mesh->RenderPass();
	}
}

VLightComponent::~VLightComponent()
{
}
