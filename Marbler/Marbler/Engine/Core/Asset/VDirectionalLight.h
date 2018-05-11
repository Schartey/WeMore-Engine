#pragma once

#include "VMesh.h"

class VDirectionalLight : public VMesh
{
public:
	VDirectionalLight();

	float GetAmbient();
	glm::vec3 GetColor();
	float GetDiffuse();
	glm::vec3 GetDirection();

	void SetAmbient(float Ambient);
	void SetColor(glm::vec3 Color);
	void SetDiffuse(float Diffuse);
	void SetDirection(glm::vec3 Direction);

	virtual void Draw() override;

	~VDirectionalLight();

private:
	glm::vec3 Direction;

	float Ambient;
	glm::vec3 Color;
	float Diffuse;

	GLuint quad_VertexArrayID;
	GLuint quad_vertexbuffer;
	GLuint size;
};