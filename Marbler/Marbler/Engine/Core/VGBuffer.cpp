#include "VGBuffer.h"

#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"

#include "Components/VCameraComponent.h"
#include "Objects/VPointLight2.h"

VGBuffer::VGBuffer()
{
}

bool VGBuffer::Initialize(int Width, int Height, int MSAASamples)
{
	GeometryShader = new VShader("Engine/Shader/gBuffer/geometry_pass.vert", "Engine/Shader/gBuffer/geometry_pass.frag");
	PointLightShader = new VShader("Engine/Shader/gBuffer/light_pass.vert", "Engine/Shader/gBuffer/pointlight_pass.frag");
	DirectionalLightShader = new VShader("Engine/Shader/gBuffer/light_pass.vert", "Engine/Shader/gBuffer/directionallight_pass.frag");
	NullShader = new VShader("Engine/Shader/gBuffer/null.vert", "Engine/Shader/gBuffer/null.frag");
	SkyboxShader = new VShader("Engine/Shader/gBuffer/skybox.vert", "Engine/Shader/gBuffer/skybox.frag");

	this->Width = Width;
	this->Height = Height;

	glGenFramebuffers(1, &gBuffer);
	glGenFramebuffers(1, &multisampleBuffer);
	BindForWriting();

	// Create the gbuffer textures
	glGenTextures(4, GBufferTextures);
	glGenTextures(1, &DepthTexture);
	glGenTextures(1, &FinalTexture);

	for (unsigned int i = 0; i < 4; i++) {
		glBindTexture(GL_TEXTURE_2D, GBufferTextures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Width, Height, 0, GL_RGB, GL_FLOAT, NULL);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, GBufferTextures[i], 0);
	}

	// depth
	glBindTexture(GL_TEXTURE_2D, DepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
		NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthTexture, 0);

	// final
	glBindTexture(GL_TEXTURE_2D, FinalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, FinalTexture, 0);

	glEnable(GL_MULTISAMPLE);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(sizeof(DrawBuffers) / sizeof(DrawBuffers[0]), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, multisampleBuffer);

	//multisample
	glGenTextures(1, &MultiSampleTexture);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, MultiSampleTexture);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, MSAASamples, GL_RGB32F, Width, Height, false);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, MultiSampleTexture, 0);
	
	// restore default FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return true;
}

void VGBuffer::StartFrame()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT4);
	glClear(GL_COLOR_BUFFER_BIT);
}

void VGBuffer::BeginGeometryPass(VScene* Scene, GLuint TestMap, GLuint ShadowMap, glm::mat4 DepthVP)
{
	BindForGeomPass();

	GeometryShader->useShader();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, ShadowMap);

	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();

	glUniform1i(glGetUniformLocation(GeometryShader->programHandle, "gShadowMap"), 10);
	glUniformMatrix4fv(glGetUniformLocation(GeometryShader->programHandle, "directionalLightVP"), 1, GL_FALSE, glm::value_ptr(DepthVP));
	glUniformMatrix4fv(glGetUniformLocation(GeometryShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(GeometryShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	// Only the geometry pass updates the depth buffer
	glDepthMask(GL_TRUE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_BLEND);
}

void VGBuffer::EndGeometryPass()
{
	// When we get here the depth buffer is already populated and the stencil pass
	// depends on it, but it does not write to it.
	//glDepthMask(GL_FALSE);

	//glDisable(GL_DEPTH_TEST);
}

void VGBuffer::StencilPass(VScene* Scene, VSceneObject* PointLight)
{
	NullShader->useShader();

	// Disable color/depth write and enable stencil
	BindForStencilPass();

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_CULL_FACE);

	glClear(GL_STENCIL_BUFFER_BIT);

	// We need the stencil test to be enabled but we want it
	// to succeed always. Only the depth test matters.
	glStencilFunc(GL_ALWAYS, 0, 0);

	glStencilOpSeparate(GL_BACK, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();
	VLightComponent* LightComponent = PointLight->GetComponentByClass<VLightComponent>();

	glUniformMatrix4fv(glGetUniformLocation(NullShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(NullShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	//Set Light
	glUniformMatrix4fv(glGetUniformLocation(NullShader->programHandle, "cmt"), 1, GL_FALSE, glm::value_ptr(LightComponent->GetGlobalModelMatrix()));

	LightComponent->LightRenderPass();
}

void VGBuffer::PointLightPass(VScene* Scene, VSceneObject* PointLight)
{
	BindForLightPass();

	PointLightShader->useShader();

	glUniform1i(glGetUniformLocation(PointLightShader->programHandle, "gPositionMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	glUniform1i(glGetUniformLocation(PointLightShader->programHandle, "gColorMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glUniform1i(glGetUniformLocation(PointLightShader->programHandle, "gNormalMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	glUniform1i(glGetUniformLocation(PointLightShader->programHandle, "gSpecularMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
	glUniform2f(glGetUniformLocation(PointLightShader->programHandle, "gScreenSize"), (float)Width, (float)Height);

	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();
	VLightComponent* LightComponent = PointLight->GetComponentByClass<VLightComponent>();

	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "eye"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetModel()));
	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "cmt"), 1, GL_FALSE, glm::value_ptr(LightComponent->GetGlobalModelMatrix()));
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "Radius"), LightComponent->GetGlobalScale().x);

	glUniform3f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Position"), LightComponent->GetGlobalPosition().x, LightComponent->GetGlobalPosition().y, LightComponent->GetGlobalPosition().z);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Base.Ambient"), LightComponent->GetPointLight().Ambient);
	glUniform3f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Base.Color"), LightComponent->GetPointLight().Color.x, LightComponent->GetPointLight().Color.y, LightComponent->GetPointLight().Color.z);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Base.Diffuse"), LightComponent->GetPointLight().Diffuse);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Atten.Constant"), LightComponent->GetPointLight().Attenuation.Constant);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Atten.Linear"), LightComponent->GetPointLight().Attenuation.Linear);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Atten.Exp"), LightComponent->GetPointLight().Attenuation.Exp);


	//glStencilFunc(GL_NOTEQUAL, 0, 0xFF);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	
	LightComponent->LightRenderPass();

	glCullFace(GL_BACK);

	glDisable(GL_BLEND);
}

void VGBuffer::DirectionalLightPass(VScene* Scene, GLuint TestMap, GLuint ShadowMap, glm::mat4 DepthVP)
{
	BindForLightPass();

	DirectionalLightShader->useShader();

	//glActiveTexture(GL_TEXTURE7);
	//glBindTexture(GL_TEXTURE_2D, ShadowMap);

	glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gPositionMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gColorMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gNormalMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gSpecularMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_SPECULAR);
	//glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gShadowMap"), 7);

	//glUniformMatrix4fv(glGetUniformLocation(GeometryShader->programHandle, "depthVP"), 1, GL_FALSE, glm::value_ptr(biasMatrix * DepthVP));
	glUniform2f(glGetUniformLocation(DirectionalLightShader->programHandle, "gScreenSize"), (float)Width, (float)Height);

	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();

	//glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "cmodel"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));
	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "eye"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetModel()));
	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "cmt"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	glUniform3f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Direction"), Scene->GetDirectionalLight()->GetDirection().x, Scene->GetDirectionalLight()->GetDirection().y, Scene->GetDirectionalLight()->GetDirection().z);
	glUniform1f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Base.Ambient"), Scene->GetDirectionalLight()->GetAmbient());
	glUniform3f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Base.Color"), Scene->GetDirectionalLight()->GetColor().x, Scene->GetDirectionalLight()->GetColor().y, Scene->GetDirectionalLight()->GetColor().z);
	glUniform1f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Base.Diffuse"), Scene->GetDirectionalLight()->GetDiffuse());

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	Scene->GetDirectionalLight()->Draw();

	glDisable(GL_BLEND);
}

void VGBuffer::DrawSkybox(VScene* Scene)
{
	//glCullFace(GL_FRONT);
	//glDepthFunc(GL_LEQUAL);

	SkyboxShader->useShader();

	VCameraComponent* CameraComponent = Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();

	glUniformMatrix4fv(glGetUniformLocation(SkyboxShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(SkyboxShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	Scene->GetSkybox()->RenderPass(SkyboxShader);

	//glDepthFunc(GL_LESS);
	//glCullFace(GL_BACK);
}

void VGBuffer::FinalPass(bool wireframeMode)
{
	//Multisample
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, multisampleBuffer);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
	if(wireframeMode)
		glReadBuffer(GL_COLOR_ATTACHMENT1);
	else
		glReadBuffer(GL_COLOR_ATTACHMENT4);

	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0, 0, Width, Height,
		0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	//Render to screen
	BindForFinalPass();
	glBlitFramebuffer(0, 0, Width, Height,
		0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

VShader* VGBuffer::GetGeometryShader()
{
	return GeometryShader;
}

void VGBuffer::BindForWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
}

void VGBuffer::BindForReading()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);

	for (unsigned int i = 0; i < 4; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, GBufferTextures[i]);
	}
}

void VGBuffer::SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + TextureType);
}

void VGBuffer::BindForGeomPass()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3};

	glDrawBuffers(sizeof(DrawBuffers) / sizeof(DrawBuffers[0]), DrawBuffers);
}

void VGBuffer::BindForStencilPass()
{
	// must disable the draw buffers 
	glDrawBuffer(GL_NONE);
}

void VGBuffer::BindForLightPass()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT4);

	for (unsigned int i = 0; i < 4; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, GBufferTextures[i]);
	}
}

void VGBuffer::BindForFinalPass()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampleBuffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
}

VGBuffer::~VGBuffer()
{
}
