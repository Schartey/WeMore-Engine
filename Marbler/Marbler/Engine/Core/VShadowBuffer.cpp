#include "VShadowBuffer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

VShadowBuffer::VShadowBuffer()
{
}

bool VShadowBuffer::Initialize(int Width, int Height)
{
	ShadowLightShader = new VShader("Engine/Shader/gBuffer/shadow_light.vert", "Engine/Shader/gBuffer/shadow_light.frag");

	this->Width = Width;
	this->Height = Height;

	glGenFramebuffers(1, &Buffer);
	BindForWriting();

	// Create the gbuffer textures

	// Test
	/*glGenTextures(1, &TestTexture);

	glBindTexture(GL_TEXTURE_2D, TestTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, Width, Height, 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TestTexture, 0);*/

	// depth
	glGenTextures(1, &DepthTexture);
	glBindTexture(GL_TEXTURE_2D, DepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTexture, 0);

	glDrawBuffer(GL_NONE); glReadBuffer(GL_NONE);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}

	// restore default FBO
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


	return true;
}

void VShadowBuffer::RenderDirectionalLightDepth(VDirectionalLight* DirectionalLight)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, Buffer);
	//glDrawBuffer(GL_COLOR_ATTACHMENT0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Clear the screen
	ShadowLightShader->useShader();

	glm::mat4 DepthProjection = glm::ortho<float>(-70, +70, -70, +70, -10, 50);
	glm::mat4 DepthViewMatrix = glm::lookAt(glm::vec3(0,0,0), DirectionalLight->GetDirection(), glm::vec3(0,1,0));
	DepthVP = DepthProjection * DepthViewMatrix;

	glUniformMatrix4fv(glGetUniformLocation(ShadowLightShader->programHandle, "depthVP"), 1, GL_FALSE, glm::value_ptr(DepthVP));

}

void VShadowBuffer::Test()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, Buffer);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0, 0, Width, Height,
		0, 0, Width, Height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}
glm::mat4 VShadowBuffer::GetDepthVP()
{
	return DepthVP;
}


GLuint VShadowBuffer::GetTestMap()
{
	return TestTexture;
}
GLuint VShadowBuffer::GetShadowMap()
{
	return DepthTexture;
}

VShader* VShadowBuffer::GetShadowLightShader()
{
	return ShadowLightShader;
}

void VShadowBuffer::BindForWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, Buffer);
}

VShadowBuffer::~VShadowBuffer()
{
}
