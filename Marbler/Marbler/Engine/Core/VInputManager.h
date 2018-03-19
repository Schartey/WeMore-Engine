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

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	static std::map<VInputKey, VActionMapping> ActionMappings;
	static std::map <int, VInputKey> inputMap;
	VInputManager();


public:
	~VInputManager();

};

