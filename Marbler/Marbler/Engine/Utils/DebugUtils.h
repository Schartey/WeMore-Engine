#pragma once

#include "GL/glew.h"

#include "../Core/VShader.h"

class DebugUtils
{
public:
	DebugUtils();

	void SetupTextureDebug();
	void DrawTexture(GLuint TextureId);

	~DebugUtils();

private:
	GLuint quad_VertexArrayID;
	GLuint quad_vertexbuffer;
	GLuint size;

	VShader* Shader;
};

