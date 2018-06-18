#pragma once

#include "IEngine.h"
#include "VGame.h"
#include "VWindow.h"
#include "Physics/VPhysics.h"
#include "VGBuffer.h"
#include "VShadowBuffer.h"
#include "../GUI/VGUI.h"
#include "../Scripting/VSquirrelEmbedder.h"

#include <string>

class VEngine : public IEngine
{
public:
	enum InitState { InitSuccess, InitGlfwError, InitWindowError, InitGlewError, InitParsingError, InitPhysicsError };

	VEngine();

	int Initialize(const char* cfgpath);
	void Setup(VGame* Game);
	void Run();
	void OnQuit();
	void OnWireFrame();

	void Pause();
	VWindow* GetWindow();
	VPhysics* GetPhysics();

	~VEngine();

private:
	Configs* config;
	VWindow * Window;
	VPhysics* Physics;
	VGUI* GUI;
	VGame * Game;
	VSquirrelEmbedder* SquirrelEmbedder;
	VSquirrelGame* SquirrelGame;

	VShadowBuffer* ShadowBuffer;
	VGBuffer* GBuffer;

	bool bPause = false;
	bool bRunning = false;
	bool wireframeMode = false;

	void StepPhysics(float deltaTime);
};

