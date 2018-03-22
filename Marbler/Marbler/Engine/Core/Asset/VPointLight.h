#pragma once

#include <string>

#include "glm/glm.hpp"

struct VAttenuation {
	float Constant = 0.0f;
	float Linear = 0.0f;
	float Exp = 32.0f;

	VAttenuation() { }
	VAttenuation(float oConstant, float oLinear, float oExp)
	{
		Constant = oConstant;
		Linear = oLinear;
		Exp = oExp;
	};
};

struct VPointLight
{
	glm::vec3 Color = glm::vec3(1.0f);
	float Ambient = 0.2f;
	float Diffuse = 0.5f;
	VAttenuation Attenuation = VAttenuation();
};