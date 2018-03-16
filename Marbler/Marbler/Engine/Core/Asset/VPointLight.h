#pragma once

#include <string>

#include "glm/glm.hpp"
#include "VMesh.h"

struct VAttenuation {
	float Constant;
	float Linear;
	float Exp;

	VAttenuation() { }
	VAttenuation(float oConstant, float oLinear, float oExp)
	{
		Constant = oConstant;
		Linear = oLinear;
		Exp = oExp;
	};
};

class VPointLight : public VMesh
{
public:

	VPointLight();

	void SetAmbient(float Ambient);
	void SetColor(glm::vec3 Color);
	void SetDiffuse(float Diffuse);
	void SetAttenuation(VAttenuation Attenuation);

	float GetAmbient();
	glm::vec3 GetColor();
	float GetDiffuse();
	VAttenuation GetAttenuation();

	virtual void Draw(glm::mat4 ParentModelMatrix) override;

	~VPointLight();

private:
	glm::vec3 Color;
	float Ambient;
	float Diffuse;

	VAttenuation Attenuation;
};