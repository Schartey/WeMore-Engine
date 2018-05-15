#include "VDebugStatics.h"

VDebugStatics* VDebugStatics::instance = 0;
int VDebugStatics::FPS = 0;

void VDebugStatics::Update(int FPS)
{
	VDebugStatics::FPS = FPS;
}

int VDebugStatics::GetFPS()
{
	return FPS;
}