#pragma once

#include "VGame.h"

class VEngine
{
public:
	enum InitState { InitSuccess, InitGlfwError, InitWindowError, InitGlewError, InitParsingError };

	VEngine();

	int Initialize(const char* cfgpath);
	int Setup(VGame* Game);
	void Run();

	~VEngine();
};

