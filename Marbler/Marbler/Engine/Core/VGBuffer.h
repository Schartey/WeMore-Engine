#pragma once

#include <vector>

#include "VShader.h"
#include "Objects/VScene.h"

#include "../Utils/DebugUtils.h"

class VGBuffer
{
public:
	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_SPECULAR,
		GBUFFER_NUM_TEXTURES
	};

	VGBuffer();

	bool Initialize(int Width, int Height, int MSAASamples);
	void StartFrame();
	void BeginGeometryPass(VScene* Scene, GLuint TestMap, GLuint ShadowMap, glm::mat4 DepthVP);
	void EndGeometryPass();
	void StencilPass(VScene* Scene, VSceneObject* PointLight);
	void PointLightPass(VScene* Scene, VSceneObject* PointLight);
	void DirectionalLightPass(VScene* Scene, GLuint TestMap, GLuint ShadowMap, glm::mat4 DepthVP);
	void DrawSkybox(VScene* Scene);
	void FinalPass(bool wireframeMode);

	VShader* GetGeometryShader();

	~VGBuffer();

private:
	int Width;
	int Height;
	glm::mat4 biasMatrix = glm::mat4(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	VShader* GeometryShader;
	VShader* PointLightShader;
	VShader* DirectionalLightShader;
	VShader* NullShader;
	VShader* SkyboxShader;

	unsigned int gBuffer;
	unsigned int multisampleBuffer;
	GLuint GBufferTextures[4];
	GLuint DepthTexture;
	GLuint MultiSampleTexture;
	GLuint FinalTexture;

	void BindForWriting();
	void BindForReading();
	void SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType);
	void BindForGeomPass();
	void BindForStencilPass();
	void BindForLightPass();
	void BindForFinalPass();

	DebugUtils* TDebugUtils;
};

