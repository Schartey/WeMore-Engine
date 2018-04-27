#pragma once

#include "glm/glm.hpp"
#include "VTexture.h"

struct Particle
{
	glm::vec4 Position;
	glm::vec4 Velocity;

	Particle(glm::vec3 Position, glm::vec3 Velocity, float TTL)
	{
		this->Position = glm::vec4(Position, TTL);
		this->Velocity = glm::vec4(Velocity, 0);
	}
};

struct VParticleDescriptor
{
public:
	glm::vec3 Position;
	glm::vec3 Velocity;
	int TTL;
	float Spread;
	int Count;

	VTexture* Texture;
};