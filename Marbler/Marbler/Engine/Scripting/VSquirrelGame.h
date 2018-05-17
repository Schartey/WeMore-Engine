#pragma once

#include "../Core/VGame.h"
#include "squirrel/squirrel.h"

class VSquirrelGame
{
public:
	VSquirrelGame(HSQUIRRELVM v, VGame* Game);

	void OnInitialize();

	~VSquirrelGame();

	static VGame * Game;

private:
	HSQUIRRELVM v;
};

