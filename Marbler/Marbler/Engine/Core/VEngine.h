#pragma once

#include "IEngine.h"
#include "VGame.h"
#include "VWindow.h"
#include "Physics/VPhysics.h"
#include "VGBuffer.h"

#include <string>

class VEngine : public IEngine
{
public:
	enum InitState { InitSuccess, InitGlfwError, InitWindowError, InitGlewError, InitParsingError, InitPhysicsError };

	VEngine();

	int Initialize(const char* cfgpath);
	void Setup(VGame* Game);
	void Run();

	void Pause();
	VWindow* GetWindow();
	VPhysics* GetPhysics();

	~VEngine();

private:
	VWindow * Window;
	VPhysics* Physics;
	VGame * Game;

	VGBuffer* GBuffer;

	bool bPause = false;
	bool bRunning = false;
};

