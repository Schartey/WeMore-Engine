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

	GLFWwindow* GetGLFWWindow() { return GlfwWindow; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetOpenGlMajor() { return openglmajor; }
	int GetOpenGlMinor() { return openglminor; }

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

