#include "VGBuffer.h"

#include "GL/glew.h"
#include "glm/gtc/type_ptr.hpp"

#include "Components/VCameraComponent.h"
#include "Asset/VPointLight.h"

VGBuffer::VGBuffer()
{
}

bool VGBuffer::Initialize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;

	glGenFramebuffers(1, &gBuffer);
	BindForWriting();

	// Create the gbuffer textures
	glGenTextures(sizeof(Textures), Textures);
	glGenTextures(1, &DepthTexture);

	for (unsigned int i = 0; i < sizeof(Textures) / sizeof(Textures[0]); i++) {
		glBindTexture(GL_TEXTURE_2D, Textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Width, Height, 0, GL_RGB, GL_FLOAT, NULL);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, Textures[i], 0);
	}

	// depth
	glBindTexture(GL_TEXTURE_2D, DepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
		NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthTexture, 0);

	// final
	glBindTexture(GL_TEXTURE_2D, FinalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGB, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, FinalTexture, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(sizeof(DrawBuffers) / sizeof(DrawBuffers[0]), DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}

	// restore default FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	GeometryShader = new VShader("Engine/Shader/gBuffer/geometry_pass.vert", "Engine/Shader/gBuffer/geometry_pass.frag");
	PointLightShader = new VShader("Engine/Shader/gBuffer/light_pass.vert", "Engine/Shader/gBuffer/pointlight_pass.frag");
	DirectionalLightShader = new VShader("Engine/Shader/gBuffer/light_pass.vert", "Engine/Shader/gBuffer/directionallight_pass.frag");
	NullShader = new VShader("Engine/Shader/gBuffer/null.vert", "Engine/Shader/gBuffer/null.frag");

	return true;
}

void VGBuffer::StartFrame()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT4);
	glClear(GL_COLOR_BUFFER_BIT);
}

void VGBuffer::BeginGeometryPass()
{
	BindForGeomPass();
	GeometryShader->useShader();

	// Only the geometry pass updates the depth buffer
	glDepthMask(GL_TRUE);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_BLEND);
}

void VGBuffer::EndGeometryPass()
{
	// When we get here the depth buffer is already populated and the stencil pass
	// depends on it, but it does not write to it.
	glDepthMask(GL_FALSE);

	glDisable(GL_DEPTH_TEST);
}

void VGBuffer::StencilPass(VScene* Scene, VPointLight* PointLight)
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

	VCameraComponent* CameraComponent = Scene->GetActivePlayerActor()->GetComponentByClass<VCameraComponent>();

	glUniformMatrix4fv(glGetUniformLocation(NullShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(NullShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	//Set Light
	glUniformMatrix4fv(glGetUniformLocation(NullShader->programHandle, "translate"), 1, GL_FALSE, glm::value_ptr(PointLight->GetTranslationMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(NullShader->programHandle, "scale"), 1, GL_FALSE, glm::value_ptr(PointLight->GetScaleMatrix()));

	PointLight->Draw(glm::mat4());
}

void VGBuffer::PointLightPass(VScene* Scene, VPointLight* PointLight)
{
	BindForLightPass();

	PointLightShader->useShader();

	glUniform1i(glGetUniformLocation(PointLightShader->programHandle, "gPositionMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	glUniform1i(glGetUniformLocation(PointLightShader->programHandle, "gColorMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glUniform1i(glGetUniformLocation(PointLightShader->programHandle, "gNormalMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	glUniform2f(glGetUniformLocation(PointLightShader->programHandle, "gScreenSize"), (float)Width, (float)Height);

	VCameraComponent* CameraComponent = Scene->GetActivePlayerActor()->GetComponentByClass<VCameraComponent>();

	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "cmodel"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	//Set Light
	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "translate"), 1, GL_FALSE, glm::value_ptr(PointLight->GetTranslationMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "scale"), 1, GL_FALSE, glm::value_ptr(PointLight->GetScaleMatrix()));

	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Base.Ambient"), PointLight->GetAmbient());
	glUniform3f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Base.Color"), PointLight->GetColor().x, PointLight->GetColor().y, PointLight->GetColor().z);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Base.Diffuse"), PointLight->GetDiffuse());
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Atten.Constant"), PointLight->GetAttenuation().Constant);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Atten.Linear"), PointLight->GetAttenuation().Linear);
	glUniform1f(glGetUniformLocation(PointLightShader->programHandle, "gPointLight.Atten.Exp"), PointLight->GetAttenuation().Exp);


	glStencilFunc(GL_NOTEQUAL, 0, 0xFF);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);


	//Set Light properties
	//glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "scale"), 1, GL_FALSE, glm::value_ptr(PointLight->GetScaleMatrix()));
	//m_DSPointLightPassTech.SetPointLight(m_pointLight[PointLightIndex]);
	
	PointLight->Draw(glm::mat4());

	glCullFace(GL_BACK);

	glDisable(GL_BLEND);
}

void VGBuffer::BeginLightPass()
{
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	BindForReading();
	glClear(GL_COLOR_BUFFER_BIT);
}

float VGBuffer::CalcPointLightBSphere(VPointLight* Light)
{
	float MaxChannel = fmax(fmax(Light->GetColor().x, Light->GetColor().y), Light->GetColor().z);

	float ret = (-Light->GetAttenuation().Linear + sqrtf(Light->GetAttenuation().Linear * Light->GetAttenuation().Linear -
		4 * Light->GetAttenuation().Exp * (Light->GetAttenuation().Exp - 256 * MaxChannel * Light->GetDiffuse()))) / (2 * Light->GetAttenuation().Exp);
	return ret;
}

void VGBuffer::DirectionalLightPass(VScene* Scene)
{
	BindForLightPass();

	DirectionalLightShader->useShader();

	glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gPositionMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
	glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gColorMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glUniform1i(glGetUniformLocation(DirectionalLightShader->programHandle, "gNormalMap"), VGBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
	glUniform2f(glGetUniformLocation(DirectionalLightShader->programHandle, "gScreenSize"), (float)Width, (float)Height);

	VCameraComponent* CameraComponent = Scene->GetActivePlayerActor()->GetComponentByClass<VCameraComponent>();

	//glUniformMatrix4fv(glGetUniformLocation(PointLightShader->programHandle, "cmodel"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "translate"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));
	glUniformMatrix4fv(glGetUniformLocation(DirectionalLightShader->programHandle, "scale"), 1, GL_FALSE, glm::value_ptr(glm::mat4()));

	glUniform3f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Direction"), Scene->GetDirectionalLight()->GetColor().x, Scene->GetDirectionalLight()->GetColor().y, Scene->GetDirectionalLight()->GetColor().z);
	glUniform1f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Base.Ambient"), Scene->GetDirectionalLight()->GetAmbient());
	glUniform3f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Base.Color"), Scene->GetDirectionalLight()->GetColor().x, Scene->GetDirectionalLight()->GetColor().y, Scene->GetDirectionalLight()->GetColor().z);
	glUniform1f(glGetUniformLocation(DirectionalLightShader->programHandle, "gDirectionalLight.Base.Diffuse"), Scene->GetDirectionalLight()->GetDiffuse());

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	Scene->GetDirectionalLight()->Draw(glm::mat4());

	glDisable(GL_BLEND);
}

void VGBuffer::FinalPass()
{
	BindForFinalPass();
	glBlitFramebuffer(0, 0, Width, Height,
		0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void VGBuffer::LightPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	BindForReading();
	
	GLsizei HalfWidth = (GLsizei)(Width / 2.0f);
	GLsizei HalfHeight = (GLsizei)(Height / 2.0f);

	SetReadBuffer(GBUFFER_TEXTURE_TYPE_POSITION);
	glBlitFramebuffer(0, 0, Width, Height, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	SetReadBuffer(GBUFFER_TEXTURE_TYPE_DIFFUSE);
	glBlitFramebuffer(0, 0, Width, Height, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	SetReadBuffer(GBUFFER_TEXTURE_TYPE_NORMAL);
	glBlitFramebuffer(0, 0, Width, Height, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	SetReadBuffer(GBUFFER_TEXTURE_TYPE_TEXCOORD);
	glBlitFramebuffer(0, 0, Width, Height, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
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
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	for (unsigned int i = 0; i < sizeof(Textures) / sizeof(Textures[0]); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
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
	glDrawBuffer(GL_COLOR_ATTACHMENT4);

	for (unsigned int i = 0; i < sizeof(Textures) / sizeof(Textures[0]); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Textures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
	}
}

void VGBuffer::BindForFinalPass()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
	glReadBuffer(GL_COLOR_ATTACHMENT4);
}

VGBuffer::~VGBuffer()
{
}