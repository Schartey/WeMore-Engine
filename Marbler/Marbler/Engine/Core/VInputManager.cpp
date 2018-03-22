#include "VInputManager.h"


std::map<VInputKey, VActionMapping> VInputManager::ActionPressedMappings;
std::map<VInputKey, VActionMapping> VInputManager::ActionReleasedMappings;
VMouseMapping VInputManager::MouseMapping;
std::map<int, VInputKey> VInputManager::inputMap;
double VInputManager::oldXPos = 0.0;
double VInputManager::oldYPos = 0.0;

VInputManager::VInputManager() {
}

void VInputManager::Initialize(VWindow* Window)
{
	inputMap[GLFW_KEY_W] = KEY_W;
	inputMap[GLFW_KEY_S] = KEY_S;
	inputMap[GLFW_KEY_A] = KEY_A;
	inputMap[GLFW_KEY_D] = KEY_D;
	inputMap[GLFW_KEY_UP] = KEY_UP;
	inputMap[GLFW_KEY_DOWN] = KEY_DOWN;
	inputMap[GLFW_KEY_LEFT] = KEY_LEFT;
	inputMap[GLFW_KEY_RIGHT] = KEY_RIGHT;
	inputMap[GLFW_KEY_SPACE] = KEY_SPACE;
	inputMap[GLFW_KEY_F5] = KEY_F5;
	inputMap[GLFW_KEY_LEFT_SHIFT] = KEY_LEFT_SHIFT;
	inputMap[GLFW_KEY_ESCAPE] = KEY_ESC;

	glfwGetCursorPos(Window->GetGLFWWindow(), &oldXPos, &oldYPos);

	glfwSetKeyCallback(Window->GetGLFWWindow(), &VInputManager::KeyCallback);
	glfwSetCursorPosCallback(Window->GetGLFWWindow(), &VInputManager::MouseCallback);
}

void VInputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (ActionPressedMappings.count(inputMap[key]) == 1)
		{
			VActionMapping Mapping = ActionPressedMappings[inputMap[key]];
			(Mapping.InputComponent->*Mapping.pmemfn)();
		}
	}
	else if(action == GLFW_RELEASE)
	{
		if (ActionReleasedMappings.count(inputMap[key]) == 1)
		{
			VActionMapping Mapping = ActionReleasedMappings[inputMap[key]];
			(Mapping.InputComponent->*Mapping.pmemfn)();
		}
	}
}

void VInputManager::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	(MouseMapping.InputComponent->*MouseMapping.pmemfn)(xpos-oldXPos, ypos-oldYPos);
	oldXPos = xpos;
	oldYPos = ypos;
}

void VInputManager::BindAction(std::string ActionName, VInputKey InputKey, VActionType ActionType, VInputComponent& InputComponent, void(VInputComponent::*pmemfn)())
{
	VActionMapping NewMapping = VActionMapping(ActionName, ActionType, &InputComponent, pmemfn);
	if(ActionType == VActionType::Pressed)
		ActionPressedMappings[InputKey] = NewMapping;
	else
		ActionReleasedMappings[InputKey] = NewMapping;
}

void VInputManager::BindMouse(VInputComponent& InputComponent, void(VInputComponent::*pmemfn)(double, double))
{
	MouseMapping = VMouseMapping();
	MouseMapping.InputComponent = &InputComponent;
	MouseMapping.pmemfn = pmemfn;
}

VInputManager::~VInputManager()
{
}
