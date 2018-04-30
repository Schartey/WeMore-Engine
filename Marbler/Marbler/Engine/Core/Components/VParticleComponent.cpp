#include "VParticleComponent.h"

#include "VCameraComponent.h"3

#include <glm/gtc/type_ptr.hpp>

VParticleComponent::VParticleComponent(VScene* Scene, std::string Name) : VSceneComponent(Scene, Name)
{
	this->Scene = Scene;

	ParticleShader = new VShader("Engine/Shader/gBuffer/particle.vert", "Engine/Shader/gBuffer/particle.geom", "Engine/Shader/gBuffer/particle.frag");
	ComputeParticleShader = new VShader("Engine/Shader/gBuffer/particle.comp");

	for (int i = 0; i < sizeof(SSBO_pos) / sizeof(GLuint); i++)
	{
		glGenBuffers(1, &SSBO_pos[i]);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_pos[i]);
		glBufferData(GL_SHADER_STORAGE_BUFFER, MAX_PARTICLES *
			sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	}

	for (int i = 0; i < sizeof(SSBO_vel) / sizeof(GLuint); i++)
	{
		glGenBuffers(1, &SSBO_vel[i]);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_vel[i]);
		glBufferData(GL_SHADER_STORAGE_BUFFER, MAX_PARTICLES *
			sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW);
	}
	glGenBuffers(1, &AtomicCounter);
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, AtomicCounter);
	glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_DRAW);

	GLuint value = 0;
	glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(GLuint), &value);
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);

	glGenBuffers(1, &Temp_Buffer);
	glBindBuffer(GL_COPY_WRITE_BUFFER, Temp_Buffer);
	glBufferData(GL_COPY_WRITE_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_READ);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);

	const GLuint position_layout = 0;
	const GLuint velocity_layout = 1;
	glGenVertexArrays(2, VAOs);

	for (int i = 0; i < 2; i++)
	{
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, SSBO_pos[i]);
		glEnableVertexAttribArray(position_layout);
		glVertexAttribPointer(position_layout, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}
}

void VParticleComponent::SetParticle(VParticleDescriptor* TParticle)
{
	this->TParticle = TParticle;

	for (int i = 0; i < TParticle->Count; i++)
	{
		//Particles.push_back(Particle(glm::vec3(GenerateFloat(TParticle->Spread), GenerateFloat(TParticle->Spread), GenerateFloat(TParticle->Spread)), glm::vec3(GenerateFloat(TParticle->Spread), GenerateFloat(TParticle->Spread), GenerateFloat(TParticle->Spread)), 0));
		Positions.push_back(glm::vec4(GenerateFloat(TParticle->Spread), GenerateFloat(TParticle->Spread), GenerateFloat(TParticle->Spread), TParticle->TTL));
		Velocities.push_back(glm::vec4(GenerateFloat(TParticle->Spread / 100), GenerateFloat(TParticle->Spread / 100), GenerateFloat(TParticle->Spread / 100), 0));
	}

	ParticleCount = Positions.size();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_pos[0]);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, ParticleCount * sizeof(Positions[0]), &Positions[0]);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_vel[0]);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, ParticleCount * sizeof(Velocities[0]), &Velocities[0]);
}

float VParticleComponent::GenerateFloat(float Max)
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX/Max);
}

void VParticleComponent::Update(double deltaT)
{
	VSceneComponent::Update(deltaT);

	ParticleCount = Positions.size();

	ComputeParticleShader->useShader();

	glUniform1ui(glGetUniformLocation(ComputeParticleShader->programHandle, "lastCount"), ParticleCount);
	glUniform1f(glGetUniformLocation(ComputeParticleShader->programHandle, "deltaT"), deltaT);
	glUniform1ui(glGetUniformLocation(ComputeParticleShader->programHandle, "maxParticles"), 1000000);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO_pos[index]);
	index = !index;

	GLuint groups = (ParticleCount / (16 * 16)) + 1;
	glDispatchCompute(groups, 1, 1);

	glMemoryBarrier(GL_ATOMIC_COUNTER_BARRIER_BIT);
	// Read atomic counter
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, AtomicCounter);

	GLuint *counterValue = (GLuint*)glMapBufferRange(
		GL_ATOMIC_COUNTER_BUFFER,
		0, sizeof(GLuint), GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	ParticleCount = counterValue[0];
	counterValue[0] = 0; // reset atomic counter
	glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER); // stop writing to buffer
											 // Make sure everything from Compute-Shader is written
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
}

void VParticleComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix, RenderPassBufferType Type)
{
	glEnable(GL_BLEND);

	ParticleShader->useShader();

	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();

	glm::mat4 CMT = ParentModelMatrix * ModelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(ParticleShader->programHandle, "cmt"), 1, GL_FALSE, glm::value_ptr(CMT));
	glUniformMatrix4fv(glGetUniformLocation(ParticleShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(ParticleShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	glBindVertexArray(VAOs[index]);

	glDrawArrays(GL_POINTS, 0, ParticleCount);

	glBindVertexArray(0);
	Shader->useShader();
	glDisable(GL_BLEND);
}

VParticleComponent::~VParticleComponent()
{
}
