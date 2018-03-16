#pragma once

#include "VActor.h"
#include "Asset/VPointLight.h"
#include "Asset/VDirectionalLight.h"

#include <vector>

class VScene
{
public:
	VScene();

	VActor* CreateActor();
	VPointLight* CreatePointLight();
	VDirectionalLight* CreateDirectionalLight();
	
	void AddPointLight(VPointLight* PointLight);
	void SetDirectionalLight(VDirectionalLight* DirectionalLight);

	std::vector<VPointLight*> GetPointLights();
	VDirectionalLight* GetDirectionalLight();

	VActor* GetActivePlayerActor();
	void SetActivePlayerActor(VActor* Actor);

	virtual void Update();
	void RenderPass(class VShader* Shader);
	void Draw();

	~VScene();

private:
	VActor * ActivePlayerActor;
	
	std::vector<VActor*> Actors;
	std::vector<VPointLight*> PointLights;
	VDirectionalLight* DirectionalLight;
};

