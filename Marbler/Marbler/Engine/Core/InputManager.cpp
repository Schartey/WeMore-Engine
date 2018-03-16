#include "InputManager.h"

#include "../Utils/Input/InputMapping.h"

InputManager::InputManager(VWindow* Window)
{
//	InputManager::vInputMapping = new InputMapping();
	glfwSetKeyCallback(Window->GetGLFWWindow(), &InputManager::KeyCallback);
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//	ActionMappings[vInputMapping->configMapping[vInputMapping->inputMap[key]]]->pmemfn();
}

void InputManager::BindAction(std::string ActionName, VActionType ActionType, VInputComponent& InputComponent, void(VInputComponent::*pmemfn)())
{
//	VActionMapping NewMapping = VActionMapping(ActionName, ActionType, &InputComponent, pmemfn);
//	ActionMappings[ActionName] = NewMapping;
}

InputManager::~InputManager()
{
}
