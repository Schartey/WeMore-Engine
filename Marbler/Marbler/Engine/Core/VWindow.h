#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VWindow
{
public:
	VWindow(std::string GameName, int width, int height, int fullscreen, int refreshrate, int openglmajor, int openglminor);

	bool Initialize(int &error);
	void Draw();

	~VWindow();

private:
	std::string GameName;
	int width;
	int height;
	int fullscreen;
	int refreshrate;
	int openglmajor;
	int openglminor;

	GLFWwindow* GlfwWindow;

};

