#include "VWindow.h"
#include "VEngine.h"
#include "Debugger.h"

#include <iostream>

#include <GLFW/glfw3.h>


VWindow::VWindow(std::string GameName, int width, int height, int fullscreen, int refreshrate, int openglmajor, int openglminor)
{
	this->GameName = GameName;
	this->width = width;
	this->height = height;
	this->fullscreen = fullscreen;
	this->refreshrate = refreshrate;
	this->openglmajor = openglmajor;
	this->openglminor = openglminor;
}

bool VWindow::Initialize(int &error)
{
	//Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW failed." << std::endl;
		error = VEngine::InitGlfwError;
		return false;
	}

#if _DEBUG
	Debugger::initDebugger();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglmajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglminor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor = nullptr;

	if (fullscreen == 1)
	{
		monitor = glfwGetPrimaryMonitor();

		if (refreshrate > 0)
			glfwWindowHint(GLFW_REFRESH_RATE, refreshrate);
	}

	GlfwWindow = glfwCreateWindow(width, height, GameName.c_str(), monitor, nullptr);

	if (!GlfwWindow)
	{
		glfwTerminate();
		std::cout << "No window." << std::endl;
		error = VEngine::InitWindowError;
		return false;
	}

	glfwMakeContextCurrent(GlfwWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		std::cout << "Could not load GLEW." << std::endl;
		error = VEngine::InitGlewError;
		return false;
	}

#if _DEBUG
	glDebugMessageCallback(Debugger::DebugCallback, NULL);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

	glEnable(GL_CULL_FACE);

	// Define the viewport dimensions
	glViewport(0, 0, width, height);

	glfwSetCursorPos(GlfwWindow, width / 2, height / 2);
	glfwSetInputMode(GlfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	return true;
}

void VWindow::Draw()
{
	glfwSwapBuffers(GlfwWindow);
}

VWindow::~VWindow()
{
}
