#include "VDirectionalLight.h"

VDirectionalLight::VDirectionalLight() : VMesh()
{
	glGenVertexArrays(1, &quad_VertexArrayID);
	glBindVertexArray(quad_VertexArrayID);

	// The fullscreen quad's FBO
	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,
	};

	size = sizeof(g_quad_vertex_buffer_data);

	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
}

float VDirectionalLight::GetAmbient()
{
	return Ambient;
}

glm::vec3 VDirectionalLight::GetColor()
{
	return Color;
}

float VDirectionalLight::GetDiffuse()
{
	return Diffuse;
}

glm::vec3 VDirectionalLight::GetDirection()
{
	return Direction;
}

void VDirectionalLight::SetAmbient(float Ambient)
{
	this->Ambient = Ambient;
}

void VDirectionalLight::SetColor(glm::vec3 Color)
{
	this->Color = Color;
}

void VDirectionalLight::SetDiffuse(float Diffuse)
{
	this->Diffuse = Diffuse;
}

void VDirectionalLight::SetDirection(glm::vec3 Direction)
{
	this->Direction = Direction;
}

void VDirectionalLight::Draw()
{
	glBindVertexArray(quad_VertexArrayID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // Starting from vertex 0; 6 vertices total -> 2 triangles
	glDisableVertexAttribArray(0);
}

VDirectionalLight::~VDirectionalLight()
{

}