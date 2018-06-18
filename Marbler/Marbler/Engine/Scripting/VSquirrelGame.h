#pragma once

#include "../Core/VGame.h"
#include "squirrel/squirrel.h"
#include "../Core/VLogger.h"

class VSquirrelGame
{
public:
	VSquirrelGame(HSQUIRRELVM v, VGame* Game);

	void OnInitialize();
	void OnUpdate(double deltaT);
	void OnHelp();
	void OnFPS();
    void OnFrustumCulling();

	~VSquirrelGame();

	static VGame * Game;
	static VLogger* Logger;

private:
	HSQUIRRELVM v;
	float time = 0.0f;
};

