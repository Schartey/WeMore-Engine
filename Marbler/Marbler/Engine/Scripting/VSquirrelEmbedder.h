#pragma once

#include "VSquirrelGame.h"

class VSquirrelEmbedder
{
public:
	VSquirrelEmbedder();

	VSquirrelGame* Setup(VGame* Game);
	void Close();

	~VSquirrelEmbedder();

private:
	HSQUIRRELVM v;
	
};

