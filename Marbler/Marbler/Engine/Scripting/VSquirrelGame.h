#pragma once

#include "../Core/VGame.h"
#include "squirrel/squirrel.h"

class VSquirrelGame
{
public:
	VSquirrelGame(HSQUIRRELVM v, VGame* Game);

	void OnInitialize();

	~VSquirrelGame();

private:
	HSQUIRRELVM v;
	VGame * Game;
};

