#pragma once

class VGame;

class VGameStatics
{
public:
	static VGameStatics* Initialize(VGame* Game) {
		if (instance == nullptr)
			instance = new VGameStatics(Game);

		return instance;
	}

	static void QuitGame();

	~VGameStatics() { delete instance; };

private:
	static VGameStatics* instance;
	static VGame* Game;

	VGameStatics(VGame* GGame) { Game = GGame; }
};

