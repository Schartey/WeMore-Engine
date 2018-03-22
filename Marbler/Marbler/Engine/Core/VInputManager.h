#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>

#include "VWindow.h"
#include "Components/VInputComponent.h"
#include "../Utils/Input/VInputKey.h"

enum VActionType {
	Pressed,
	Released
};

struct VMouseMapping {
	VInputComponent* InputComponent;
	void(VInputComponent::*pmemfn)(double, double);
};

struct VActionMapping {
	std::string ActionName;
	VActionType ActionType;
	VInputComponent* InputComponent;
	void(VInputComponent::*pmemfn)();

	VActionMapping() {}
	VActionMapping(std::string iActionName, VActionType iActionType, VInputComponent* iInputComponent, void(VInputComponent::*ipmemfn)()) {
		ActionName = iActionName;
		ActionType = iActionType;
		InputComponent = iInputComponent;
		pmemfn = ipmemfn;
	}
};

class VInputManager
{
public:
	static void Initialize(VWindow* Window);
	static void BindAction(std::string ActionName, VInputKey InputKey, VActionType ActionType, VInputComponent& InputComponent, void(VInputComponent::*pmemfn)());
	static void BindMouse(VInputComponent& InputComponent, void(VInputComponent::*pmemfn)(double, double));
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

private:

	static std::map<VInputKey, VActionMapping> ActionPressedMappings;
	static std::map<VInputKey, VActionMapping> ActionReleasedMappings;
	static VMouseMapping MouseMapping;
	static std::map <int, VInputKey> inputMap;

	static double oldXPos;
	static double oldYPos;

	VInputManager();


public:
	~VInputManager();

};

