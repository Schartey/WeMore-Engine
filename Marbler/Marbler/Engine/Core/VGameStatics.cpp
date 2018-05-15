#include "VGameStatics.h"

#include "VGame.h"

VGameStatics* VGameStatics::instance = 0;
VGame* VGameStatics::Game = 0;

VGame* VGameStatics::GetGame()
{
	return Game;
}
