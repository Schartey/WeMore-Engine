#include "VSceneComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

VSceneComponent::VSceneComponent()
{
}

void VSceneComponent::Translate(glm::vec3 vector)
{
	TranslationMatrix = glm::translate(TranslationMatrix, vector);
}

void VSceneComponent::Draw()
{

}


VSceneComponent::~VSceneComponent()
{
}
