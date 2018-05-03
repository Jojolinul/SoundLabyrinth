#pragma once
#include "GameState.h"
#include "InputManager.h"
#include "Background.h"
#include "Player.h"
#include "Game.h"
#include "ScreenManager.h"

class MenuState : public GameState
{
public:
	MenuState();

	bool Update(double deltaTime);
	bool Draw();

	~MenuState() {}

private:
	Player camera;
	Background bg;

	bool pressEnter = false;
	const Uint8* keys = nullptr;
};

