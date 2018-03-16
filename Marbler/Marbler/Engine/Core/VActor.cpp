#include "VActor.h"

#include "../Utils/Assimp/VAssimpUtils.h"
#include "Components/VMeshComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

VActor::VActor(VScene* Scene)
{
	this->Scene = Scene;
}

void VActor::Translate(glm::vec3 vector)
{
	TranslationMatrix = glm::translate(TranslationMatrix, vector);

	ModelMatrix = TranslationMatrix * RotationMatrix*ScaleMatrix;
}

glm::mat4 VActor::GetModelMatrix()
{
	return ModelMatrix;
}

void VActor::Update()
{
	for (VActorComponent* ActorComponent : ActorComponents)
	{
		ActorComponent->Update();
	}
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Update();
	}
}

void VActor::RenderPass(VShader* Shader)
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->RenderPass(Shader, ModelMatrix);
	}
}

void VActor::Draw()
{
	for (VSceneComponent* SceneComponent : SceneComponents)
	{
		SceneComponent->Draw(ModelMatrix);
	}
}


VActor::~VActor()
{
}
