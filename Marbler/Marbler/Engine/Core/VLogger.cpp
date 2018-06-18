#include "VLogger.h"

VLogger* VLogger::Instance = 0;

VLogger::VLogger()
{
}

void VLogger::Debug(std::string prefix, std::string message)
{
	if (this->Mode == EMode::Debug)
	{
		printf((prefix + " - Debug: " + message + "\n").c_str());
	}
}

void VLogger::Info(std::string prefix, std::string message)
{
	printf((prefix + " - Info: " + message + "\n").c_str());
}

void VLogger::Warning(std::string prefix, std::string message)
{
	printf((prefix + " - Warning: " + message + "\n").c_str());
}

void VLogger::Error(std::string prefix, std::string message)
{
	printf((prefix + " - Error: " + message + "\n").c_str());
}

void VLogger::SetMode(EMode Mode)
{
	this->Mode = Mode;
}
