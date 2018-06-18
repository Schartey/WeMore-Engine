#pragma once

#include <string>

class VLogger
{
public:
	enum class EMode {
		Debug,
		Info,
		Warning,
		Error
	};

	static VLogger* GetInstance() {
		if (Instance == nullptr)
			Instance = new VLogger();

		return Instance;
	}

	void Debug(std::string prefix, std::string message);
	void Info(std::string prefix, std::string message);
	void Warning(std::string prefix, std::string message);
	void Error(std::string prefix, std::string message);

	void SetMode(EMode Mode);

	~VLogger() {
		delete Instance;
	};

private:
	VLogger();

	static VLogger* Instance;

	EMode Mode;
};

