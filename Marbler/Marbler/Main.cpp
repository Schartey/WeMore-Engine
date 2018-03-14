#include "Engine/Core/VEngine.h"

#include "Game/Marbler.h"

int main(int argc, char** argv)
{
	VEngine* engine = new VEngine();
	engine->Initialize("config.json");
	engine->Setup(new Marbler());
	engine->Run();
}