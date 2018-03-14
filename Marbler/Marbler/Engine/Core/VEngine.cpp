#include "VEngine.h"
#include "../Utils/Configs.h"

VEngine::VEngine()
{
}

int VEngine::Initialize(const char* cfgpath)
{
	Configs* config = new Configs();

	if (!config->readFile(cfgpath)) {
		std::cout << "Could not read config file" << std::endl;
		return InitParsingError;
	}

	std::string GameName = config->getValue("name", "Game Name").asString();

	int width = config->getValue("width", "800").asInt();
	int height = config->getValue("height", "600").asInt();

	int fullscreen = config->getValue("fullscreen", "0").asInt();
	int refreshrate = config->getValue("refreshrate", "0").asInt();

	int openglmajor = config->getValue("openglmajor", "4").asInt();
	int openglminor = config->getValue("openglminor", "3").asInt();

	Window = new VWindow(GameName, width, height, fullscreen, refreshrate, openglmajor, openglminor);
	int error;

	if (!Window->Initialize(error))
	{
		std::cout << "Creating window failed." << std::endl;
		return error;
	}

	Physics = new VPhysics();
	
	if (!Physics->Initialize())
	{
		std::cout << "Creating physics failed." << std::endl;
		return InitPhysicsError;
	}

	return InitSuccess;
}

void VEngine::Setup(VGame* Game)
{
	this->Game = Game;
	this->Game->SetWindow(Window);

	this->Game->OnInitialize();
}

void VEngine::Run()
{
	bRunning = true;
	auto deltaT = 0.0;
	auto lastTime = glfwGetTime();
	double lastTimeMS = glfwGetTime();

	while (bRunning)
	{
		auto time = glfwGetTime();
		deltaT = (float)(time - lastTime);
		lastTime = time;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glfwPollEvents();

		if (!bPause) {
			//Game->updatePhysics();
			//Game->update(deltaT);
			Game->Draw();
		}

		//_game->drawGUI();
		//_gui->draw();

		Window->Draw();
	}
}

void VEngine::Pause()
{
	bPause = true;
}

VWindow* VEngine::GetWindow()
{
	return Window;
}


VEngine::~VEngine()
{
}
