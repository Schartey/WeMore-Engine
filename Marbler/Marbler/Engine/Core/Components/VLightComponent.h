#pragma once

#include "VMeshComponent.h"
#include "../Asset/VPointLight.h"
#include "../Asset/VDirectionalLight.h"

enum LightType {
	PointLight,
	DirectionalLight,
	SpotLight
};
class VLightComponent : public VMeshComponent
{
public:
	VLightComponent(VScene* Scene, std::string Name, LightType lightType);
	~VLightComponent();

	glm::vec3 GetGlobalPosition();
	glm::vec3 GetGlobalScale();
	LightType GetLightType();
	VPointLight& GetPointLight();

	virtual void RenderPass(VShader* Shader, glm::mat4 ParentMatrix, RenderPassBufferType Type) override;
	virtual void LightRenderPass();

private:
	LightType lightType;
	VPointLight PointLight = VPointLight();
	//VDirectionalLight DirectionalLight = VDirectionalLight();
};

