#include "VSceneComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

VSceneComponent::VSceneComponent()
{
}

glm::mat4 VSceneComponent::GetModelMatrix()
{
	return ModelMatrix;
}

void VSceneComponent::Translate(glm::vec3 vector)
{
	TranslationMatrix = glm::translate(TranslationMatrix, vector);
}

void VSceneComponent::RenderPass(VShader* Shader, glm::mat4 ParentModelMatrix)
{

}

void VSceneComponent::Draw(glm::mat4 ParentModelMatrix)
{

}


VSceneComponent::~VSceneComponent()
{
}
