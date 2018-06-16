#include "VScene.h"

#include "VActor.h"
#include "../../Utils/Assimp/VAssimpUtils.h"

VScene::VScene(std::string Name)
{
	// setup default scene
	this->Name = Name;
	PhysicsScene = VPhysics::GetInstance()->CreateDefaultScene();
}

VActor* VScene::CreateActor(std::string Name)
{
	VActor* Actor = new VActor(this, Name);
	SceneObjects.push_back(Actor);
	return Actor;
}

VPointLight2* VScene::CreatePointLight(std::string Name)
{
	VPointLight2* PointLight = new VPointLight2(this, Name);
	SceneObjects.push_back(PointLight);
	return PointLight;
}

VSkybox* VScene::CreateSkybox(std::string Name, VTextureCube* TextureCube)
{
	this->Skybox = new VSkybox(this, Name, TextureCube);
	return Skybox;
}

VSkybox* VScene::GetSkybox()
{
	return this->Skybox;
}
/*VPointLight* VScene::CreatePointLight()
{
	VPointLight* PointLight = new VPointLight();
	return PointLight;
}*/

VDirectionalLight* VScene::CreateDirectionalLight(float brightness)
{
	std::string modelPath = "Models\\";
	VDirectionalLight* DirectionalLight = VAssimpUtils::LoadDirectionalLight(modelPath + "box.fbx");
	DirectionalLight->SetAmbient(brightness); //config->getValue("brightness", "0.0").asFloat()
	DirectionalLight->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	DirectionalLight->SetDiffuse(0.6f);
	DirectionalLight->SetDirection(glm::vec3(0.0f, -1.0f, 0.5f));

	this->SetDirectionalLight(DirectionalLight);

	return DirectionalLight;
}

/*void VScene::AddPointLight(VPointLight* PointLight)
{
	PointLights.push_back(PointLight);
}*/

void VScene::SetDirectionalLight(VDirectionalLight* DirectionalLight)
{
	this->DirectionalLight = DirectionalLight;
}

std::vector<VSceneObject*> VScene::GetPointLights()
{
	//Might be better to just make a vector of pointlights and store there addiontally instead of only sceneobejcts (no querying then)
	std::vector<VSceneObject*> PointLights;

	for (VSceneObject* SceneObject : SceneObjects)
	{
		VLightComponent* Object = SceneObject->GetComponentByClass<VLightComponent>();

		if (Object != nullptr && Object->GetLightType() == LightType::PointLight)
		{
			PointLights.push_back(SceneObject);
		}
	}
	return PointLights;
}

VDirectionalLight* VScene::GetDirectionalLight()
{
	return DirectionalLight;
}

PxScene* VScene::GetPhysicsScene()
{
	return PhysicsScene;
}

std::string VScene::GetName()
{
	return this->Name;
}

VSceneObject* VScene::GetActiveSceneObject()
{
	return ActiveSceneObject;
}

void VScene::SetActiveSceneObject(VSceneObject* SceneObject)
{
	this->ActiveSceneObject = SceneObject;
}

void VScene::Update(double deltaT)
{
	for (VSceneObject* Actor : SceneObjects)
	{
		Actor->Update(deltaT);
	}
}

void VScene::RenderPass(VShader* Shader, RenderPassBufferType Type)
{
	for (VSceneObject* Actor : SceneObjects)
	{
		Actor->RenderPass(Shader, Type);
	}
}

void VScene::Draw()
{
	for (VSceneObject* Actor : SceneObjects)
	{
		Actor->Draw();
	}
}

VScene::~VScene()
{
}
