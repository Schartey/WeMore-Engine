#pragma once

#include "VWindow.h"

class IEngine
{
public:
	virtual void Pause() = 0;
	virtual VWindow* GetWindow() = 0;
};

