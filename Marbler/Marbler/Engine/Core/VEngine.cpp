#include "VEngine.h"
#include "IL/il.h"
#include "VInputManager.h"
#include "VDebugStatics.h"
#include "VLogger.h"

VEngine::VEngine()
{
}

int VEngine::Initialize(const char* cfgpath)
{
	config = new Configs();

	if (!config->readFile(cfgpath)) {
		std::cout << "Could not read config file" << std::endl;
		return InitParsingError;
	}

	std::string debugMode = config->getValue("debug", "false").asString();
	if (debugMode.compare("true") == 0) 
	{
		VLogger::GetInstance()->SetMode(VLogger::EMode::Debug);
	}
	else 
	{
		VLogger::GetInstance()->SetMode(VLogger::EMode::Info);
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

	Physics = VPhysics::GetInstance();

	if (!Physics->Initialize())
	{
		std::cout << "Creating physics failed." << std::endl;
		return InitPhysicsError;
	}

	VTextEngine::GetInstance()->Setup(width, height);
	GUI = new VGUI();

	SquirrelEmbedder = new VSquirrelEmbedder();

	VInputManager::Initialize(Window);

	ilInit();

	return InitSuccess;
}

void VEngine::Setup(VGame* Game)
{
	GBuffer = new VGBuffer();
	GBuffer->Initialize(Window->GetWidth(), Window->GetHeight(), config->getValue("msaa", "1").asInt());

	ShadowBuffer = new VShadowBuffer();
	ShadowBuffer->Initialize(Window->GetWidth(), Window->GetHeight());

	this->Game = Game;
	this->Game->OnQuitDelegate = std::bind(&VEngine::OnQuit, this);
	this->Game->OnWireFrameDelegate = std::bind(&VEngine::OnWireFrame, this);
	this->Game->OnRecompileDelegate = std::bind(&VEngine::OnRecompileSquirrel, this);
	this->Game->SetConfig(config);
	this->Game->SetWindow(Window);
	this->Game->SetPhysics(Physics);
	this->Game->SetGUI(GUI);

	SquirrelGame = SquirrelEmbedder->Setup(this->Game);
	SquirrelGame->OnInitialize();
}

void VEngine::Run()
{
	bRunning = true;
	auto deltaT = 0.0;
	auto lastTime = glfwGetTime();
	double lastTimeMS = glfwGetTime();
	double physicsTime = 0;
	double startupTime = 0;

	while (bRunning)
	{
		auto time = glfwGetTime();
		deltaT = (float)(time - lastTime);
		lastTime = time;

		VDebugStatics::Update((int)(deltaT * 10000));
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glfwPollEvents();


		if (!bPause && deltaT > 0) {
			startupTime += deltaT;

			if(startupTime > 1)
				physicsTime += deltaT;

			if (physicsTime > 0.01667)
			{
				StepPhysics(physicsTime);
				physicsTime = 0;
			}
			SquirrelGame->OnUpdate(deltaT);
			VDebugStatics::Objects = 0;

			if (Window->GetOpenGlMinor() >= 0) {
				if (!wireframeMode)
				{
					ShadowBuffer->RenderDirectionalLightDepth(Game->GetActiveScene()->GetDirectionalLight());
					Game->RenderPass(ShadowBuffer->GetShadowLightShader(), RenderPassBufferType::ShadowBuffer);
				}
				//ShadowBuffer->Test();
				//Game->GetActiveScene()->GetSkybox()->RenderPass();
				GBuffer->StartFrame();
				GBuffer->BeginGeometryPass(Game->GetActiveScene(), ShadowBuffer->GetTestMap(), ShadowBuffer->GetShadowMap(), ShadowBuffer->GetDepthVP());
				Game->RenderPass(GBuffer->GetGeometryShader(), RenderPassBufferType::GBuffer);
				GBuffer->EndGeometryPass();

				if (!wireframeMode)
				{
					glEnable(GL_STENCIL_TEST);

					for (unsigned int i = 0; i < Game->GetActiveScene()->GetPointLights().size(); i++) {
						GBuffer->StencilPass(Game->GetActiveScene(), Game->GetActiveScene()->GetPointLights().at(i));
						GBuffer->PointLightPass(Game->GetActiveScene(), Game->GetActiveScene()->GetPointLights().at(i));
					}
					glDisable(GL_STENCIL_TEST);

					if (Game->GetActiveScene()->GetDirectionalLight() != nullptr)
					{
						GBuffer->DirectionalLightPass(Game->GetActiveScene(), ShadowBuffer->GetTestMap(), ShadowBuffer->GetShadowMap(), ShadowBuffer->GetDepthVP());
					}
				}

				//Draw Skybox
				//GBuffer->DrawSkybox(Game->GetActiveScene());
				GUI->RenderPass();

				GBuffer->FinalPass(wireframeMode);
			}
			else
			{
				Game->Draw();
			}
		}

		//_game->drawGUI();
		//_gui->draw();
		Window->Draw();
	}
	SquirrelEmbedder->Close();
}

void VEngine::OnQuit()
{
	bRunning = false;
}

void VEngine::OnWireFrame()
{
	if (wireframeMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else 
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	wireframeMode = !wireframeMode;
}

void VEngine::OnRecompileSquirrel()
{
	SquirrelEmbedder->Close();
	GUI = new VGUI();
	this->Game->SetGUI(GUI);
	SquirrelGame = SquirrelEmbedder->Setup(this->Game);
	SquirrelGame->OnInitialize();
}

void VEngine::Pause()
{
	bPause = true;
}

VWindow* VEngine::GetWindow()
{
	return Window;
}

VPhysics* VEngine::GetPhysics()
{
	return Physics;
}

void VEngine::StepPhysics(float deltaTime)
{
	PX_UNUSED(false);
	Game->GetActiveScene()->GetPhysicsScene()->simulate(deltaTime);
	Game->GetActiveScene()->GetPhysicsScene()->fetchResults(true);
}

//TODO StopEngine -> maybe register at delegate in game

VEngine::~VEngine()
{
}
