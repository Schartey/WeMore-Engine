#include "Engine/Core/VEngine.h"

int main(int argc, char** argv)
{
	VEngine* engine = new VEngine();
	engine->Initialize("config.json");
	engine->Setup(new VGame());
	engine->Run();
}