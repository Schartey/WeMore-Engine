#pragma once

#include "VActor.h"
#include "VPointLight2.h"
//#include "../Asset/VPointLight.h"
#include "../Asset/VDirectionalLight.h"

#include <vector>

#include "../Physics/VPhysics.h"

class VScene
{
public:
	VScene(std::string Name);

	VActor* CreateActor(std::string Name);
	VPointLight2* CreatePointLight(std::string Name);
	VDirectionalLight* CreateDirectionalLight();
	
	//void AddPointLight(VPointLight* PointLight);
	void SetDirectionalLight(VDirectionalLight* DirectionalLight);

	std::vector<VSceneObject*> GetPointLights();
	VDirectionalLight* GetDirectionalLight();

	PxScene* GetPhysicsScene();

	std::string GetName();
	VSceneObject* GetActiveSceneObject();
	void SetActiveSceneObject(VSceneObject* Actor);

	virtual void Update(double deltaT);
	void RenderPass(class VShader* Shader, RenderPassBufferType Type);
	void Draw();

	~VScene();

private:
	std::string Name;
	VSceneObject * ActiveSceneObject;
	
	std::vector<VSceneObject*> SceneObjects;
	//std::vector<VPointLight*> PointLights;
	VDirectionalLight* DirectionalLight;

	PxScene* PhysicsScene;
};

