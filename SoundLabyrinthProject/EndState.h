#pragma once
#include "GameState.h"
#include "InputManager.h"
#include "Background.h"
#include "Player.h"
#include "Game.h"
#include "ScreenManager.h"

class EndState : public GameState
{
public:
	EndState();

	bool Update(double deltaTime);
	bool Draw();

	~EndState() {}

private:
	Player camera;
	Background bg;

	double count = 0;
	const Uint8* keys = nullptr;
};

