#include "VSkybox.h"

#include "../../Utils/Assimp/VAssimpUtils.h"
#include "../Components/VCameraComponent.h"
#include "../Objects/VScene.h"

#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

VSkybox::VSkybox(VScene* Scene, std::string Name, VTextureCube* TextureCube) : VSceneObject(Scene, Name)
{
	SkyboxShader = new VShader("Engine/Shader/gBuffer/skybox.vert", "Engine/Shader/gBuffer/skybox.frag");
	this->TextureCube = TextureCube;

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);

	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->Vertices), this->Vertices, GL_STATIC_DRAW);
}

void VSkybox::RenderPass()
{
	glDepthMask(GL_FALSE);
	SkyboxShader->useShader();

	VCameraComponent* CameraComponent = this->Scene->GetActiveSceneObject()->GetComponentByClass<VCameraComponent>();
	glm::mat4 view = glm::mat4(glm::mat3(CameraComponent->GetViewMatrix()));
	// ... set view and projection matrix
	glUniformMatrix4fv(glGetUniformLocation(SkyboxShader->programHandle, "view"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(SkyboxShader->programHandle, "projection"), 1, GL_FALSE, glm::value_ptr(CameraComponent->GetProjectionMatrix()));

	glUniform1i(glGetUniformLocation(SkyboxShader->programHandle, ("skybox")), 0);

	glBindVertexArray(this->VAO);
	TextureCube->Bind(0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

VSkybox::~VSkybox()
{
}
