#pragma once

#include <vector>

#include "VSceneComponent.h"
#include "../Asset/VTexture.h"
#include "../Asset/VParticle.h"

#include "../VShader.h"
#include "../Objects/VScene.h"

class VParticleComponent : public VSceneComponent
{
public:
	VParticleComponent(VScene* Scene, std::string Name);

	void SetParticle(VParticleDescriptor* TParticle);

	virtual void Update(double deltaT) override;
	virtual void RenderPass(class VShader* Shader, glm::mat4 ParentModelMatrix) override;

	~VParticleComponent();

private:
	GLuint VAOs[2];
	GLuint SSBO_pos[2];
	GLuint SSBO_vel[2];
	GLuint AtomicCounter;
	GLuint Temp_Buffer;

	VShader* ParticleShader;
	VShader* ComputeParticleShader;

	VParticleDescriptor* TParticle;

	//std::vector<Particle> Particles;
	std::vector<glm::vec4> Positions;
	std::vector<glm::vec4> Velocities;

	int ParticleCount = 0;

	float GenerateFloat(float Max);

	int index = 0;
	int WORK_GROUP_SIZE = 256;
	int MAX_PARTICLES = 1000000;

	VScene* Scene;
};

