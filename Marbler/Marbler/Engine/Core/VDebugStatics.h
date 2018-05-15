#pragma once

class VDebugStatics
{
public:
	static VDebugStatics* Initialize() {
		if (instance == nullptr)
			instance = new VDebugStatics();

		return instance;
	}

	static void Update(int FPS);
	static int GetFPS();

	~VDebugStatics() { delete instance; };

private:
	static VDebugStatics* instance;

	static int FPS;

	VDebugStatics() { }
};
