#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>

#include "VWindow.h"
#include "Components/VInputComponent.h"

enum VActionType {
	Pressed,
	Released
};

struct VActionMapping {
	std::string ActionName;
	VActionType ActionType;
	VInputComponent* InputComponent;
	void(VInputComponent::*pmemfn)();

	VActionMapping(std::string iActionName, VActionType iActionType, VInputComponent* iInputComponent, void(VInputComponent::*ipmemfn)()) {
		ActionName = iActionName;
		ActionType = iActionType;
		InputComponent = iInputComponent;
		pmemfn = ipmemfn;
	}
};

class InputManager
{
public:

	InputManager(VWindow* Window);

	void BindAction(std::string ActionName, VActionType ActionType, VInputComponent& InputComponent, void(VInputComponent::*pmemfn)());
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	~InputManager();

private:
//	static InputMapping* vInputMapping;

//	static std::map<std::string, VActionMapping> ActionMappings;

};

