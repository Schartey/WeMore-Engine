#pragma once

#include "VShader.h"
#include "Asset/VDirectionalLight.h"

class VShadowBuffer
{
public:
	VShadowBuffer();

	bool Initialize(int Width, int Height);

	void RenderDirectionalLightDepth(VDirectionalLight* DirectionalLight);

	glm::mat4 GetDepthVP();
	GLuint GetTestMap();
	GLuint GetShadowMap();
	VShader* GetShadowLightShader();

	void Test();
	~VShadowBuffer();

private:
	int Width;
	int Height;

	glm::mat4 DepthVP;

	VShader* ShadowLightShader;

	unsigned int Buffer;

	GLuint TestTexture;
	GLuint DepthTexture;

	void BindForWriting();

};

