#pragma once

#include <vector>

#include "VShader.h"
#include "VScene.h"

class VGBuffer
{
public:
	enum GBUFFER_TEXTURE_TYPE {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_TEXCOORD,
		GBUFFER_NUM_TEXTURES
	};

	VGBuffer();

	bool Initialize(int Width, int Height);
	void StartFrame();
	void BeginGeometryPass();
	void EndGeometryPass();
	void StencilPass(VScene* Scene, VPointLight* PointLight);
	void PointLightPass(VScene* Scene, VPointLight* PointLight);
	void BeginLightPass();
	void DirectionalLightPass(VScene* Scene);
	void FinalPass();
	void LightPass();

	VShader* GetGeometryShader();

	~VGBuffer();

private:
	int Width;
	int Height;

	VShader* GeometryShader;
	VShader* PointLightShader;
	VShader* DirectionalLightShader;
	VShader* NullShader;

	unsigned int gBuffer;
	GLuint Textures[GBUFFER_NUM_TEXTURES];
	GLuint DepthTexture;
	GLuint FinalTexture;

	float CalcPointLightBSphere(VPointLight* Light);

	void BindForWriting();
	void BindForReading();
	void SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType);
	void BindForGeomPass();
	void BindForStencilPass();
	void BindForLightPass();
	void BindForFinalPass();
};

