#pragma once

#include <string>
#include <map>

#include <GLFW/glfw3.h>

enum VInputKey {
	KEY_W,
	KEY_S,
	KEY_A,
	KEY_D,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_1,
	KEY_2,
	KEY_SPACE,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_ESC,
	KEY_LEFT_SHIFT,
	KEY_UNKOWN
};

class InputMapping
{

public:
	InputMapping();

	VInputKey ParseSomeEnum(const std::string &value)
	{
		std::map <std::string, VInputKey>::const_iterator iValue = inputStringMap.find(value);
		if (iValue == inputStringMap.end())
			return KEY_UNKOWN;
		return iValue->second;
	}

	std::map <int, VInputKey> inputMap;
	std::map <std::string, VInputKey> inputStringMap;
	std::map <VInputKey, std::string> configMapping;
};

InputMapping::InputMapping()
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

	inputStringMap["W"] = KEY_W;
	inputStringMap["S"] = KEY_S;
	inputStringMap["A"] = KEY_A;
	inputStringMap["D"] = KEY_D;
	inputStringMap["UP"] = KEY_UP;
	inputStringMap["DOWN"] = KEY_DOWN;
	inputStringMap["LEFT"] = KEY_LEFT;
	inputStringMap["RIGHT"] = KEY_RIGHT;
	inputStringMap["SPACE"] = KEY_SPACE;
	inputStringMap["F5"] = KEY_F5;
	inputStringMap["LEFT_SHIFT"] = KEY_LEFT_SHIFT;
	inputStringMap["ESCAPE"] = KEY_ESC;
}
