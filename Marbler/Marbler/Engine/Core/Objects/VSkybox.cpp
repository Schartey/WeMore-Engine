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

void VSkybox::RenderPass(VShader* Shader)
{
	glUniform1i(glGetUniformLocation(Shader->programHandle, ("skybox")), 0);

	glBindVertexArray(this->VAO);
	TextureCube->Bind(0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

VSkybox::~VSkybox()
{
}
